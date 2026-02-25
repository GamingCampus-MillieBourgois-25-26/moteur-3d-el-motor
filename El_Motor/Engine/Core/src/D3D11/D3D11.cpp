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
			&pSwapChain,
			&pDevice,
			nullptr,// Feature Level
			&pContext
		);
		Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer = nullptr;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&pBackBuffer); // Récupère le buffer de rendu arrière du swap chain
		if (pDevice != nullptr) {
			pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget); // Crée une vue de rendu à partir du buffer de rendu arrière
		}

		// === CHARGEMENT DES SHADERS (UNE SEULE FOIS) ===
		wrl::ComPtr<ID3DBlob> blob;

		HRESULT hr = D3DReadFileToBlob(L"Shader/VertexShader.cso", &blob);
		if (FAILED(hr)) { std::cout << "Vertex shader load failed\n"; return; }

		hr = pDevice->CreateVertexShader(blob->GetBufferPointer(),
			blob->GetBufferSize(),
			nullptr,
			&mVertexShader);
		if (FAILED(hr)) { std::cout << "CreateVertexShader failed\n"; return; }

		hr = D3DReadFileToBlob(L"Shader/PixelShader.cso", &blob);
		if (FAILED(hr)) { std::cout << "Pixel shader load failed\n"; return; }

		hr = pDevice->CreatePixelShader(blob->GetBufferPointer(),
			blob->GetBufferSize(),
			nullptr,
			&mPixelShader);
		if (FAILED(hr)) { std::cout << "CreatePixelShader failed\n"; return; }

		// === INPUT LAYOUT (basé sur le VS) ===
		const D3D11_INPUT_ELEMENT_DESC layout[] =
		{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24,D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		hr = pDevice->CreateInputLayout(
			layout,
			(UINT)std::size(layout),
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			&mInputLayout);

		if (FAILED(hr)) { std::cout << "CreateInputLayout failed\n"; return; }
	}

	IDXGIAdapter1* D3D11::searchForAdapters() {
		wrl::ComPtr<IDXGIFactory1> pFactory = nullptr; // Pointeur pour la factory DXGI
		CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&pFactory); // On créé une instance de la factory DXGI pour pouvoir énumérer les adaptateurs disponibles

		IDXGIAdapter1* pAdapter = nullptr;
		IDXGIAdapter1* bestAdapter = nullptr;
		SIZE_T maxVRam = 0;

		for (UINT i = 0; pFactory->EnumAdapters1(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
			DXGI_ADAPTER_DESC1 desc;
			pAdapter->GetDesc1(&desc);
			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
				continue; // Ignore les adaptateurs logiciels
			if (desc.DedicatedVideoMemory > maxVRam) {
				maxVRam = desc.DedicatedVideoMemory;
				bestAdapter = pAdapter; // Met à jour le meilleur adaptateur trouvé jusqu'à présent
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
		float clearColor[] = { r, g, b, 1.0f }; // Couleur de nettoyage (RGBA)
		pContext->ClearRenderTargetView(pTarget.Get(), clearColor); // Nettoie la vue de rendu avec la couleur spécifiée
		if (!pTarget) return;
	}

	void D3D11::DrawShape(const MeshAsset& mesh)
	{
		// === SHADERS ===
		pContext->VSSetShader(mVertexShader.Get(), nullptr, 0);
		pContext->PSSetShader(mPixelShader.Get(), nullptr, 0);

		// === INPUT LAYOUT ===
		pContext->IASetInputLayout(mInputLayout.Get());

		// === MESH BIND (MeshAsset) ===
		mesh.Bind(pContext.Get());

		// === RENDER TARGET ===
		wrl::ComPtr<ID3D11RenderTargetView> pTarget = GetRenderTargetView();
		pContext->OMSetRenderTargets(1, pTarget.GetAddressOf(), nullptr);

		// === VIEWPORT ===
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

		// === DRAW ===
		pContext->DrawIndexed(mesh.GetIndexCount(), 0, 0);
	}

}