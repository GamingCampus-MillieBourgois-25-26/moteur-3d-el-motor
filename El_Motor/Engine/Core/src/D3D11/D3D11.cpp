#include "D3D11/D3D11.hpp"

#include <d3dcompiler.h>
#include <wrl.h>
#include <memory>
#include <iostream>

#pragma comment(lib, "d3dcompiler.lib")

namespace Engine
{
	D3D11::D3D11(GLFWwindow* window) {
		myWindow = glfwGetWin32Window(window); // Récupère le handle de la fenêtre à partir de GLFW
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
		ID3D11Resource* pBackBuffer = nullptr;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&pBackBuffer); // Récupère le buffer de rendu arrière du swap chain
		if (pDevice != nullptr) {
			pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pTarget); // Crée une vue de rendu à partir du buffer de rendu arrière
		}
		pBackBuffer->Release(); // Libère le buffer de rendu arrière, car il n'est plus nécessaire après la création de la vue de rendu
	}

	D3D11::~D3D11() {
		if (pSwapChain != nullptr) pSwapChain->Release(); // Libère le swap chain
		if (pContext != nullptr) pContext->Release(); // Libère le contexte de rendu
		if (pDevice != nullptr) pDevice->Release(); // Libère le device
		if (pTarget != nullptr) pTarget->Release(); // Libère la vue de rendu
	}


	IDXGIAdapter1* D3D11::searchForAdapters() {
		IDXGIFactory1* pFactory = nullptr; // Pointeur pour la factory DXGI
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
		pContext->ClearRenderTargetView(pTarget, clearColor); // Nettoie la vue de rendu avec la couleur spécifiée
	}


	void Engine::D3D11::DrawTriangleTest()
	{
		namespace wrl = Microsoft::WRL;
		HRESULT hr;

		struct Vertex {
			float x, y;
		};

		// Triangle centré, bien visible
		const Vertex vertices[] = {
			{ 0.0f,  0.9f },
			{ 0.9f, -0.9f },
			{-0.9f, -0.9f }
		};

		// --- Vertex buffer ---
		ID3D11Buffer* pVertexBuffer = nullptr;
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(vertices);
		bufferDesc.StructureByteStride = sizeof(Vertex);

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = vertices;

		hr = pDevice->CreateBuffer(&bufferDesc, &initData, &pVertexBuffer);
		if (FAILED(hr)) { std::cout << "Failed to create vertex buffer\n"; return; }

		const UINT stride = sizeof(Vertex);
		const UINT offset = 0;
		pContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

		// --- Shaders ---
		ID3DBlob* pBlob = nullptr;
		ID3D11PixelShader* pPixelShader = nullptr;
		hr = D3DReadFileToBlob(L"Shader/PixelShader.cso", &pBlob);
		if (FAILED(hr)) { std::cout << "Pixel shader load failed\n"; return; }
		hr = pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
		if (FAILED(hr)) { std::cout << "CreatePixelShader failed\n"; return; }
		pContext->PSSetShader(pPixelShader, nullptr, 0);

		ID3D11VertexShader* pVertexShader = nullptr;
		hr = D3DReadFileToBlob(L"Shader/VertexShader.cso", &pBlob);
		if (FAILED(hr)) { std::cout << "Vertex shader load failed\n"; return; }
		hr = pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
		if (FAILED(hr)) { std::cout << "CreateVertexShader failed\n"; return; }
		pContext->VSSetShader(pVertexShader, nullptr, 0);

		// --- Input layout ---
		ID3D11InputLayout* pInputLayout = nullptr;
		const D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		hr = pDevice->CreateInputLayout(inputElementDesc, (UINT)std::size(inputElementDesc),
			pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);
		if (FAILED(hr)) { std::cout << "CreateInputLayout failed\n"; return; }
		pContext->IASetInputLayout(pInputLayout);

		// --- Bind render target ---
		pContext->OMSetRenderTargets(1, &pTarget, nullptr);
		pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// --- Viewport dynamique ---
		RECT rect;
		GetClientRect(myWindow, &rect);
		float width = static_cast<float>(rect.right - rect.left);
		float height = static_cast<float>(rect.bottom - rect.top);

		D3D11_VIEWPORT viewport = {};
		viewport.Width = width;
		viewport.Height = height;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		pContext->RSSetViewports(1, &viewport);

		// --- Draw call ---
		pContext->Draw((UINT)std::size(vertices), 0);

	}

}