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
		~D3D11();

		IDXGIAdapter* searchForAdapters();

	private:
		HWND myWindow;
		ID3D11Device* pDevice = nullptr;
		ID3D11DeviceContext* pContext = nullptr;
		IDXGISwapChain* pSwapChain = nullptr;
	};
}