#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32 // permet le glfwGetWin32Window() d'être défini
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <d3d11_1.h>
#include <d3d11.h>
#include <dxgi.h>
#include <vector>
#include <wrl.h>
#include <DirectXMath.h>


#include <Windows.h> // pour HWND et API Windows
#include "Window/IWindow.hpp"
#include "Maths/Headers/MMatrix4.hpp"


class MeshAsset;
class Material;

namespace wrl = Microsoft::WRL;



namespace Engine {

	struct MatrixBuffer
	{
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
		DirectX::XMMATRIX vp;
	};

	struct ObjectColorBuffer
	{
		DirectX::XMFLOAT3 objColor;
		int useTexture;
	};

	class D3D11 {
	public:
		D3D11(IWindow& window);
		D3D11(const D3D11& other) = delete; // Interdit la copie
		D3D11& operator=(const D3D11& other) = delete; // Interdit l'assignation

		~D3D11() = default;

		void Present(); // Permet de présenter le swap chain à l'écran
		void ClearBackBuffer(float r, float g, float b) noexcept; // Permet de nettoyer le back buffer avec une couleur spécifiée
		void SetViewProjection(const Maths::Mat4f& vp);
		ID3D11Device* GetDevice() const noexcept { return pDevice.Get(); }
		ID3D11DeviceContext* GetContext() const noexcept { return pContext.Get(); }
		IDXGISwapChain* GetSwapChain() const noexcept { return pSwapChain.Get(); }
		ID3D11RenderTargetView* GetRenderTargetView() const noexcept { return pTarget.Get(); }
		void DrawShape(const MeshAsset& mesh, const Material& material);
	private:
		HWND myWindow;
		wrl::ComPtr <ID3D11Device> pDevice = nullptr;
		wrl::ComPtr <ID3D11DeviceContext> pContext = nullptr;
		wrl::ComPtr <IDXGISwapChain> pSwapChain = nullptr;
		wrl::ComPtr <ID3D11RenderTargetView> pTarget = nullptr;
		wrl::ComPtr<ID3D11DepthStencilView> mDepthStencilView;
		wrl::ComPtr<ID3D11SamplerState> mSampler;

		wrl::ComPtr<ID3D11Buffer> mObjectColorBuffer;
		wrl::ComPtr<ID3D11Buffer> mMatrixBuffer;

		wrl::ComPtr<ID3D11VertexShader> mVertexShader;
		wrl::ComPtr<ID3D11PixelShader>  mPixelShader;
		wrl::ComPtr<ID3D11InputLayout>  mInputLayout;

		IDXGIAdapter1* searchForAdapters(); // permet de rechercher les adaptateurs disponibles et de choisir le meilleur
		DXGI_SWAP_CHAIN_DESC initSwapChainDesc(); // permet d'initialiser la description du swap chain avec les paramètres souhaités
	};
}