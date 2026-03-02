#include "D3D11/D3D11.hpp"
#include "Assets/MeshAsset/MeshAsset.hpp"

#include <d3dcompiler.h>
#include <wrl.h>
#include <memory>
#include <iostream>


#pragma comment(lib, "d3dcompiler.lib")

namespace Engine
{
	D3D11::D3D11(IWindow& window)
	{
		myWindow = static_cast<HWND>(window.GetNativeWindow());
		DXGI_SWAP_CHAIN_DESC swapChainDesc = initSwapChainDesc(); // variable locale pour la description du swap chain, initialisée avec les paramètres souhaités

		D3D11CreateDeviceAndSwapChain(
			searchForAdapters(), // Adapter
			D3D_DRIVER_TYPE_UNKNOWN,// Driver Type
			nullptr,// Software
			0,	// Flags
			nullptr, 0, // Feature Levels
			D3D11_SDK_VERSION,
			&swapChainDesc, // Utilise la variable locale, qui est une l-value
			pSwapChain.GetAddressOf(),
			pDevice.GetAddressOf(),
			nullptr,// Feature Level
			pContext.GetAddressOf()
		);
		Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer = nullptr;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&pBackBuffer); // Récupère le buffer de rendu arrière du swap chain
		if (pDevice != nullptr) {
			pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, pTarget.GetAddressOf()); // Crée une vue de rendu à partir du buffer de rendu arrière
		}

		// Récup taille de la fenêtre
		RECT rect;
		GetClientRect(myWindow, &rect);
		UINT width = rect.right - rect.left;
		UINT height = rect.bottom - rect.top;

		// Description de la texture depth
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

		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = TRUE;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

		wrl::ComPtr<ID3D11DepthStencilState> depthState;
		pDevice->CreateDepthStencilState(&dsDesc, depthState.GetAddressOf());
		pContext->OMSetDepthStencilState(depthState.Get(), 0);


		// === CHARGEMENT DES SHADERS (UNE SEULE FOIS) ===
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


		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(ObjectColorBuffer);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		pDevice->CreateBuffer(&bd, nullptr, mObjectColorBuffer.GetAddressOf());

		hr = pDevice->CreateInputLayout(
			layout,
			(UINT)std::size(layout),
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			&mInputLayout);

		if (FAILED(hr)) { std::cout << "CreateInputLayout failed\n"; return; }
	}

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


	DXGI_SWAP_CHAIN_DESC D3D11::initSwapChainDesc() {
		DXGI_SWAP_CHAIN_DESC SwapChDesc = {};
		SwapChDesc.BufferDesc.Width = 800; // Largeur du buffer
		SwapChDesc.BufferDesc.Height = 600; // Hauteur du buffer
		SwapChDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Format du buffer
		SwapChDesc.BufferDesc.RefreshRate.Numerator = 60; // Taux de rafraîchissement (numérateur)
		SwapChDesc.BufferDesc.RefreshRate.Denominator = 1; // Taux de rafraîchissement (dénominateur)
		SwapChDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; // Type de scaling
		SwapChDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // Ordre de balayage
		SwapChDesc.SampleDesc.Count = 1; // Nombre d'échantillons pour l'anti-aliasing
		SwapChDesc.SampleDesc.Quality = 0; // Qualité de l'anti-aliasing
		SwapChDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Usage du buffer
		SwapChDesc.BufferCount = 1; // Nombre de buffers
		SwapChDesc.OutputWindow = myWindow; // Fenêtre de sortie
		SwapChDesc.Windowed = TRUE; // Mode fenêtré
		SwapChDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Effet de swap
		SwapChDesc.Flags = 0; // Flags supplémentaires
		return SwapChDesc; // Retourne la description du swap chain
	}


	void D3D11::Present() {
		pSwapChain->Present(1u, 0); // Présente le swap chain à l'écran, avec un intervalle de synchronisation de 1
	}

	void D3D11::ClearBackBuffer(float r, float g, float b) noexcept {
		float clearColor[] = { r, g, b, 1.0f };
		if (!pTarget) return;
		pContext->ClearRenderTargetView(pTarget.Get(), clearColor);

		if (mDepthStencilView)
			pContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void D3D11::DrawShape(const MeshAsset& mesh)
	{
		// Récupère le render target
		wrl::ComPtr<ID3D11RenderTargetView> pTarget = GetRenderTargetView();
		if (!pTarget || !mDepthStencilView) return;

		// 1. Bind le render target + depth stencil
		pContext->OMSetRenderTargets(1, pTarget.GetAddressOf(), mDepthStencilView.Get());

		// 2. Clear la frame (couleur + depth)
		float clearColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		pContext->ClearRenderTargetView(pTarget.Get(), clearColor);
		pContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

		// 3. Configure le viewport
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

		// 4. Active les shaders
		pContext->VSSetShader(mVertexShader.Get(), nullptr, 0);
		pContext->PSSetShader(mPixelShader.Get(), nullptr, 0);

		// 5. Input layout
		pContext->IASetInputLayout(mInputLayout.Get());

		// 6. Bind le mesh
		mesh.Bind(pContext.Get());

		// 7. Constant buffer pour la couleur
		ObjectColorBuffer buffer;
		DirectX::XMFLOAT3 colorConv = DirectX::XMFLOAT3(mesh.GetColor().m_x, mesh.GetColor().m_y, mesh.GetColor().m_z);
		buffer.objColor = colorConv;
		buffer.padding = 0.0f;

		pContext->UpdateSubresource(
			mObjectColorBuffer.Get(),
			0,
			nullptr,
			&buffer,
			0,
			0
		);

		pContext->PSSetConstantBuffers(0, 1, mObjectColorBuffer.GetAddressOf());

		// 8. Draw le mesh
		pContext->DrawIndexed(mesh.GetIndexCount(), 0, 0);
	}
}