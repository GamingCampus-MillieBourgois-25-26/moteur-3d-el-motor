#include "D3D11/D3D11.hpp"
#include "Assets/MeshAsset/MeshAsset.hpp"
#include "Assets/TextureAsset/Material.hpp"

#include <d3dcompiler.h>
#include <wrl.h>
#include <memory>
#include <iostream>

#pragma comment(lib, "d3dcompiler.lib")

namespace Engine
{
	// Constructeur : initialise D3D11, swap chain, shaders, render target et depth stencil
	D3D11::D3D11(IWindow& window)
	{
		myWindow = static_cast<HWND>(window.GetNativeWindow());

		// Création de la description du swap chain
		DXGI_SWAP_CHAIN_DESC swapChainDesc = initSwapChainDesc();

		// Création du device D3D11 + swap chain
		D3D11CreateDeviceAndSwapChain(
			searchForAdapters(),
			D3D_DRIVER_TYPE_UNKNOWN,
			nullptr,
			0,
			nullptr, 0,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			pSwapChain.GetAddressOf(),
			pDevice.GetAddressOf(),
			nullptr,
			pContext.GetAddressOf()
		);

		// Récupération du back buffer
		Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer = nullptr;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&pBackBuffer);
		if (pDevice != nullptr) {
			pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, pTarget.GetAddressOf());
		}

		// Récupération taille de la fenêtre
		RECT rect;
		GetClientRect(myWindow, &rect);
		UINT width = rect.right - rect.left;
		UINT height = rect.bottom - rect.top;

		// Création de la texture depth
		D3D11_TEXTURE2D_DESC depthDesc = {};
		depthDesc.Width = width;
		depthDesc.Height = height;
		depthDesc.MipLevels = 1;
		depthDesc.ArraySize = 1;
		depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthDesc.SampleDesc.Count = 1;
		depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		wrl::ComPtr<ID3D11Texture2D> depthTexture;
		HRESULT hr = pDevice->CreateTexture2D(&depthDesc, nullptr, depthTexture.GetAddressOf());
		if (FAILED(hr)) { std::cout << "Depth texture creation failed\n"; return; }

		hr = pDevice->CreateDepthStencilView(
			depthTexture.Get(),
			nullptr,
			mDepthStencilView.GetAddressOf()
		);
		if (FAILED(hr)) { std::cout << "DepthStencilView creation failed\n"; return; }

		// Depth stencil state
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = TRUE;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

		wrl::ComPtr<ID3D11DepthStencilState> depthState;
		pDevice->CreateDepthStencilState(&dsDesc, depthState.GetAddressOf());
		pContext->OMSetDepthStencilState(depthState.Get(), 0);

		// === CHARGEMENT DES SHADERS (une seule fois) ===
		wrl::ComPtr<ID3DBlob> vsBlob;
		wrl::ComPtr<ID3DBlob> psBlob;

		hr = D3DReadFileToBlob(L"Shader/VertexShader.cso", vsBlob.GetAddressOf());
		if (FAILED(hr)) { std::cout << "Vertex shader load failed\n"; return; }

		hr = pDevice->CreateVertexShader(vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			nullptr,
			&mVertexShader);
		if (FAILED(hr)) { std::cout << "CreateVertexShader failed\n"; return; }

		hr = D3DReadFileToBlob(L"Shader/PixelShader.cso", psBlob.GetAddressOf());
		if (FAILED(hr)) { std::cout << "Pixel shader load failed\n"; return; }

		hr = pDevice->CreatePixelShader(psBlob->GetBufferPointer(),
			psBlob->GetBufferSize(),
			nullptr,
			&mPixelShader);
		if (FAILED(hr)) { std::cout << "CreatePixelShader failed\n"; return; }

		// === INPUT LAYOUT (basé sur le VS) ===
		const D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, position),D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, normal),D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(Vertex, uv),D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		// Constant buffer pour couleur/texture
		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(ObjectColorBuffer);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		hr = pDevice->CreateBuffer(&bd, nullptr, mObjectColorBuffer.GetAddressOf());
		if (FAILED(hr)) {
			std::cout << "Failed to create ObjectColor constant buffer, hr=" << std::hex << hr << std::endl;
			return;
		}

		hr = pDevice->CreateInputLayout(
			layout,
			(UINT)std::size(layout),
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			&mInputLayout);

		if (FAILED(hr)) { std::cout << "CreateInputLayout failed\n"; return; }

		D3D11_SAMPLER_DESC sampDesc = {};
		sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.MaxAnisotropy = 16;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		hr = pDevice->CreateSamplerState(&sampDesc, mSampler.GetAddressOf());
		if (FAILED(hr))
		{
			std::cout << "Failed to create sampler state\n";
		}

		D3D11_BUFFER_DESC mbDesc = {};
		mbDesc.Usage = D3D11_USAGE_DEFAULT;
		mbDesc.ByteWidth = sizeof(MatrixBuffer);
		mbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		hr = pDevice->CreateBuffer(&mbDesc, nullptr, mMatrixBuffer.GetAddressOf());
	}

	// Sélection du meilleur adapter DXGI (VRAM max)
	IDXGIAdapter1* D3D11::searchForAdapters()
	{
		wrl::ComPtr<IDXGIFactory1> pFactory = nullptr;
		CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&pFactory);

		IDXGIAdapter1* pAdapter = nullptr;
		IDXGIAdapter1* bestAdapter = nullptr;
		SIZE_T maxVRam = 0;

		for (UINT i = 0; pFactory->EnumAdapters1(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
		{
			DXGI_ADAPTER_DESC1 desc;
			pAdapter->GetDesc1(&desc);

			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
				continue;

			if (desc.DedicatedVideoMemory > maxVRam)
			{
				maxVRam = desc.DedicatedVideoMemory;
				bestAdapter = pAdapter;
			}
		}

		return bestAdapter;
	}

	// Description par défaut du swap chain
	DXGI_SWAP_CHAIN_DESC D3D11::initSwapChainDesc() {
		DXGI_SWAP_CHAIN_DESC SwapChDesc = {};
		SwapChDesc.BufferDesc.Width = 0;
		SwapChDesc.BufferDesc.Height = 0;
		SwapChDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		SwapChDesc.BufferDesc.RefreshRate.Numerator = 60;
		SwapChDesc.BufferDesc.RefreshRate.Denominator = 1;
		SwapChDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		SwapChDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		SwapChDesc.SampleDesc.Count = 1;
		SwapChDesc.SampleDesc.Quality = 0;
		SwapChDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapChDesc.BufferCount = 1;
		SwapChDesc.OutputWindow = myWindow;
		SwapChDesc.Windowed = TRUE;
		SwapChDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		SwapChDesc.Flags = 0;
		return SwapChDesc;
	}

	// Présentation du back buffer à l'écran
	void D3D11::Present() {
		pSwapChain->Present(1u, 0);
	}

	// Nettoyage back buffer + depth stencil
	void D3D11::ClearBackBuffer(float r, float g, float b) noexcept {
		float clearColor[] = { r, g, b, 1.0f };
		if (!pTarget) return;
		pContext->ClearRenderTargetView(pTarget.Get(), clearColor);

		if (mDepthStencilView)
			pContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void D3D11::SetViewProjection(const Maths::Mat4f& vp)
	{
		MatrixBuffer mb{};

		DirectX::XMMATRIX m = DirectX::XMMatrixTranspose(
			DirectX::XMLoadFloat4x4((DirectX::XMFLOAT4X4*)&vp)
		);

		mb.view = DirectX::XMMatrixIdentity();
		mb.projection = DirectX::XMMatrixIdentity();
		mb.vp = m;

		pContext->UpdateSubresource(
			mMatrixBuffer.Get(),
			0,
			nullptr,
			&mb,
			0,
			0
		);

		pContext->VSSetConstantBuffers(
			0,
			1,
			mMatrixBuffer.GetAddressOf()
		);
	}

	// Fonction de rendu d’un mesh avec material
	void D3D11::DrawShape(const MeshAsset& mesh, const Material& material)
	{
		// Bind render target + depth stencil
		wrl::ComPtr<ID3D11RenderTargetView> pTarget = GetRenderTargetView();
		if (!pTarget || !mDepthStencilView) return;

		pContext->OMSetRenderTargets(1, pTarget.GetAddressOf(), mDepthStencilView.Get());

		// Clear frame
		float clearColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		pContext->ClearRenderTargetView(pTarget.Get(), clearColor);
		pContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

		// Configure viewport
		RECT rect;
		GetClientRect(myWindow, &rect);
		D3D11_VIEWPORT viewport = {};
		viewport.Width = float(rect.right - rect.left);
		viewport.Height = float(rect.bottom - rect.top);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		pContext->RSSetViewports(1, &viewport);

		// Active shaders
		pContext->VSSetShader(mVertexShader.Get(), nullptr, 0);
		pContext->PSSetShader(mPixelShader.Get(), nullptr, 0);


		// Input layout
		pContext->IASetInputLayout(mInputLayout.Get());

		pContext->PSSetSamplers(0, 1, mSampler.GetAddressOf());

		// Bind mesh et material
		mesh.Bind(pContext.Get());
		material.Bind(pContext.Get());

		if (!mObjectColorBuffer)
		{
			std::cout << "ObjectColor buffer is null, skipping draw\n";
			return;
		}

		// Constant buffer couleur
		ObjectColorBuffer buffer;
		buffer.objColor = material.color;
		buffer.useTexture = material.texture && material.texture->IsReady() ? 1 : 0;

		pContext->UpdateSubresource(
			mObjectColorBuffer.Get(),
			0,
			nullptr,
			&buffer,
			0,
			0
		);

		pContext->PSSetConstantBuffers(0, 1, mObjectColorBuffer.GetAddressOf());

		// Draw call
		pContext->DrawIndexed(mesh.GetIndexCount(), 0, 0);
	}


}