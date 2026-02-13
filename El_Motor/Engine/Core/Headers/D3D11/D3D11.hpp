#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32 // permet le glfwGetWin32Window() d'être défini
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <d3d11_1.h>
#include <d3d11.h>
#include <dxgi.h>

#include <Windows.h> // pour HWND et API Windows

namespace Engine {
	class D3D11 {
	public:
		D3D11(GLFWwindow* window);
		D3D11(const D3D11& other) = delete; // Interdit la copie
		D3D11& operator=(const D3D11& other) = delete; // Interdit l'assignation

		~D3D11();

		void Present(); // Permet de présenter le swap chain à l'écran
		void ClearBackBuffer(float r, float g, float b) noexcept; // Permet de nettoyer le back buffer avec une couleur spécifiée

		void DrawTriangleTest();

	private:
		HWND myWindow;
		ID3D11Device* pDevice = nullptr;
		ID3D11DeviceContext* pContext = nullptr;
		IDXGISwapChain* pSwapChain = nullptr;
		ID3D11RenderTargetView* pTarget = nullptr;

		IDXGIAdapter1* searchForAdapters(); // permet de rechercher les adaptateurs disponibles et de choisir le meilleur
		DXGI_SWAP_CHAIN_DESC initSwapChainDesc(); // permet d'initialiser la description du swap chain avec les paramètres souhaités
	};
}