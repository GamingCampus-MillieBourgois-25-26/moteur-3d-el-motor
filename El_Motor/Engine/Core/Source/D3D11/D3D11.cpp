#include "../Core/Headers/D3D11/D3D11.hpp"

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


	void D3D11::DrawTriangleTest() 
	{
		namespace wrl = Microsoft::WRL; // Alias pour simplifier l'utilisation des ComPtr

		struct Vertex {
			float x, y; // Position du sommet
		};

		const Vertex vertices[] = {
			{ 0.0f, 0.5f}, // Sommet supérieur
			{ 0.5f, -0.5f}, // Sommet inférieur droit
			{ -0.5f, -0.5f} // Sommet inférieur gauche
		};

		wrl::ComPtr<ID3D11Buffer> pVertexBuffer; // ComPtr est un smartPointer spécial pour les ressources type COM (Components Object Model)
		D3D11_BUFFER_DESC bufferDesc = {}; // Description du buffer de vertex
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Indique que ce buffer sera utilisé comme buffer de vertex
		bufferDesc.Usage = D3D11_USAGE_DEFAULT; // Indique que le buffer sera utilisé de manière standard (lecture/écriture par le GPU)
		bufferDesc.CPUAccessFlags = 0; // Pas d'accès CPU nécessaire
		bufferDesc.MiscFlags = 0; // Pas de flags supplémentaires
		bufferDesc.ByteWidth = sizeof(vertices); // Taille totale du buffer en bytes (nombre de sommets * taille d'un sommet)
		bufferDesc.StructureByteStride = sizeof(Vertex); // Taille d'un sommet en bytes

		D3D11_SUBRESOURCE_DATA initData = {}; // Données initiales pour le buffer de vertex
		initData.pSysMem = vertices; // Pointeur vers les données des sommets

		pDevice->CreateBuffer(&bufferDesc, &initData,&pVertexBuffer);
		const UINT stride = sizeof(Vertex); // Taille d'un sommet en bytes (utilisée pour lier le buffer de vertex)
		const UINT offset = 0u; // Offset dans le buffer de vertex (généralement 0 pour commencer au début)
		pContext->IASetVertexBuffers(0u, 1u, &pVertexBuffer,&stride, &offset);

		wrl::ComPtr<ID3D11VertexShader> pVertexShader;
		wrl::ComPtr<ID3DBlob> pBlob;

		HRESULT hr = D3DReadFileToBlob(L"../../Headers/Shader/VertexShader.cso", &pBlob);

		if (FAILED(hr)) {
			if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) {
				std::cout << "Erreur : fichier VertexShader.cso non trouvé !" << std::endl;
			}
			else {
				std::cout << "Erreur : impossible de lire VertexShader.cso, code HRESULT = 0x"
					<< std::hex << hr << std::dec << std::endl;
			}
			return; // Sort de la fonction, on ne peut pas continuer
		}

		std::cout << "VertexShader.cso chargé avec succès !" << std::endl;

		// Si on arrive ici, pBlob est valide
		pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

		pContext->VSSetShader(pVertexShader.Get(), nullptr, 0); // Lie le vertex shader au pipeline de rendu
		pContext->Draw(std::size(vertices), 0); // Dessine un triangle
	}
}