#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32 // Allows glfwGetWin32Window() to be defined
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <d3d11_1.h>
#include <d3d11.h>
#include <dxgi.h>
#include <vector>
#include <wrl.h>
#include <DirectXMath.h>

#include <Windows.h> // Required for HWND and Windows API
#include "Window/IWindow.hpp"
#include "Maths/Headers/MMatrix4.hpp"

class MeshAsset;
class Material;

namespace wrl = Microsoft::WRL;

namespace Engine {

	/// <summary>
	/// Constant buffer used to store camera matrices.
	/// Sent to the GPU each frame.
	/// </summary>
	struct MatrixBuffer
	{
		DirectX::XMMATRIX view;        // View matrix
		DirectX::XMMATRIX projection;  // Projection matrix
		DirectX::XMMATRIX vp;          // Combined ViewProjection matrix
	};

	/// <summary>
	/// Constant buffer used to send object color data to the pixel shader.
	/// </summary>
	struct ObjectColorBuffer
	{
		DirectX::XMFLOAT3 objColor; // Base color of the object
		int useTexture;             // Flag indicating whether a texture is used
	};

	/// <summary>
	/// Wrapper class responsible for initializing and managing Direct3D 11.
	/// Handles device creation, swap chain, rendering targets, and draw calls.
	/// </summary>
	class D3D11 {
	public:

		/// <summary>
		/// Constructs the D3D11 renderer using the provided window.
		/// </summary>
		/// <param name="window">Window interface used to retrieve the native handle</param>
		D3D11(IWindow& window);

		/// Disable copy constructor
		D3D11(const D3D11& other) = delete;

		/// Disable assignment operator
		D3D11& operator=(const D3D11& other) = delete;

		/// <summary>
		/// Default destructor
		/// </summary>
		~D3D11() = default;

		/// <summary>
		/// Presents the swap chain to the screen (displays the rendered frame).
		/// </summary>
		void Present();

		/// <summary>
		/// Clears the back buffer with the specified color.
		/// </summary>
		/// <param name="r">Red component</param>
		/// <param name="g">Green component</param>
		/// <param name="b">Blue component</param>
		void ClearBackBuffer(float r, float g, float b) noexcept;

		/// <summary>
		/// Updates the view-projection matrix used by the shaders.
		/// </summary>
		/// <param name="vp">ViewProjection matrix</param>
		void SetViewProjection(const Maths::Mat4f& vp);

		/// <summary>
		/// Returns the D3D11 device.
		/// </summary>
		ID3D11Device* GetDevice() const noexcept { return pDevice.Get(); }

		/// <summary>
		/// Returns the D3D11 device context.
		/// </summary>
		ID3D11DeviceContext* GetContext() const noexcept { return pContext.Get(); }

		/// <summary>
		/// Returns the swap chain.
		/// </summary>
		IDXGISwapChain* GetSwapChain() const noexcept { return pSwapChain.Get(); }

		/// <summary>
		/// Returns the render target view.
		/// </summary>
		ID3D11RenderTargetView* GetRenderTargetView() const noexcept { return pTarget.Get(); }

		/// <summary>
		/// Draws a mesh using the provided material.
		/// </summary>
		/// <param name="mesh">Mesh asset containing vertex/index buffers</param>
		/// <param name="material">Material containing textures and parameters</param>
		void DrawShape(const MeshAsset& mesh, const Material& material);

	private:

		/// <summary>
		/// Native window handle used for DirectX initialization.
		/// </summary>
		HWND myWindow;

		/// <summary>
		/// Direct3D device responsible for resource creation.
		/// </summary>
		wrl::ComPtr<ID3D11Device> pDevice = nullptr;

		/// <summary>
		/// Device context used for rendering commands.
		/// </summary>
		wrl::ComPtr<ID3D11DeviceContext> pContext = nullptr;

		/// <summary>
		/// Swap chain used to present frames to the screen.
		/// </summary>
		wrl::ComPtr<IDXGISwapChain> pSwapChain = nullptr;

		/// <summary>
		/// Render target view representing the back buffer.
		/// </summary>
		wrl::ComPtr<ID3D11RenderTargetView> pTarget = nullptr;

		/// <summary>
		/// Depth stencil buffer used for depth testing.
		/// </summary>
		wrl::ComPtr<ID3D11DepthStencilView> mDepthStencilView;

		/// <summary>
		/// Sampler state used for texture sampling.
		/// </summary>
		wrl::ComPtr<ID3D11SamplerState> mSampler;

		/// <summary>
		/// Constant buffer storing object color parameters.
		/// </summary>
		wrl::ComPtr<ID3D11Buffer> mObjectColorBuffer;

		/// <summary>
		/// Constant buffer storing camera matrices.
		/// </summary>
		wrl::ComPtr<ID3D11Buffer> mMatrixBuffer;

		/// <summary>
		/// Vertex shader used for rendering meshes.
		/// </summary>
		wrl::ComPtr<ID3D11VertexShader> mVertexShader;

		/// <summary>
		/// Pixel shader used for fragment shading.
		/// </summary>
		wrl::ComPtr<ID3D11PixelShader>  mPixelShader;

		/// <summary>
		/// Input layout describing vertex structure.
		/// </summary>
		wrl::ComPtr<ID3D11InputLayout>  mInputLayout;

		/// <summary>
		/// Searches for available GPU adapters and selects the best one.
		/// </summary>
		/// <returns>Pointer to the selected adapter</returns>
		IDXGIAdapter1* searchForAdapters();

		/// <summary>
		/// Initializes the swap chain description with desired parameters.
		/// </summary>
		/// <returns>Configured swap chain description</returns>
		DXGI_SWAP_CHAIN_DESC initSwapChainDesc();
	};
}