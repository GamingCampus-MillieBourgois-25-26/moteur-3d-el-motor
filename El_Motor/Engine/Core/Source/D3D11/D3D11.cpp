#include "../Core/Headers/D3D11/D3D11.hpp"



Engine::D3D11::D3D11(GLFWwindow* window) {
	myWindow = glfwGetWin32Window(window); // Récupère le handle de la fenêtre à partir de GLFW
	D3D11CreateDeviceAndSwapChain( 
		searchForAdapters(),				  // Adapter
		D3D_DRIVER_TYPE_UNKNOWN, // Driver Type
		nullptr,				  // Software
		0,						  // Flags
		nullptr, 0,				  // Feature Levels
		D3D11_SDK_VERSION,
		nullptr,				  // Swap Chain Desc
		&pSwapChain,
		&pDevice,
		nullptr,				  // Feature Level
		&pContext
	);
}

Engine::D3D11::~D3D11() {
}

IDXGIAdapter* Engine::D3D11::searchForAdapters() {
	IDXGIFactory* pFactory = nullptr; // Pointeur pour la factory DXGI
	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory); // Crée une instance de la factory DXGI

	IDXGIAdapter* pAdapter = nullptr;
	IDXGIAdapter* bestAdapter = nullptr;
	SIZE_T maxVRam = 0; 

	for (UINT i = 0; pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i) { // Parcourt les adaptateurs disponibles
		DXGI_ADAPTER_DESC desc; // Structure pour stocker les informations de l'adaptateur
		pAdapter->GetDesc(&desc); // Récupère la description de l'adaptateur
		if (desc.DedicatedVideoMemory > maxVRam) { // Si cet adaptateur a plus de VRAM que le meilleur trouvé jusqu'à présent
			maxVRam = desc.DedicatedVideoMemory; // Met à jour la quantité maximale de VRAM
			bestAdapter = pAdapter; // Met à jour le meilleur adaptateur
		}
	}
	return bestAdapter; // Retourne le meilleur adaptateur trouvé
}