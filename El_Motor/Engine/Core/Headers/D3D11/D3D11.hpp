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

    /**
     * @brief Constant buffer used to store camera matrices.
     *
     * This buffer is sent to the GPU each frame to update view and projection transformations.
     */
    struct MatrixBuffer
    {
        DirectX::XMMATRIX view;        ///< View matrix
        DirectX::XMMATRIX projection;  ///< Projection matrix
        DirectX::XMMATRIX vp;          ///< Combined ViewProjection matrix
    };

    /**
     * @brief Constant buffer used to send object color data to the pixel shader.
     */
    struct ObjectColorBuffer
    {
        DirectX::XMFLOAT3 objColor; ///< Base color of the object
        int useTexture;             ///< Flag indicating whether a texture is used
    };

    /**
     * @brief Wrapper class responsible for initializing and managing Direct3D 11.
     *
     * Handles device creation, swap chain, render targets, shaders, and draw calls.
     */
    class D3D11 {
    public:

        /**
         * @brief Constructs the D3D11 renderer using the provided window.
         * @param window Window interface used to retrieve the native handle
         */
        D3D11(IWindow& window);

        /// Disable copy constructor
        D3D11(const D3D11& other) = delete;

        /// Disable assignment operator
        D3D11& operator=(const D3D11& other) = delete;

        /// @brief Default destructor
        ~D3D11() = default;

        /**
         * @brief Presents the swap chain to the screen (displays the rendered frame)
         */
        void Present();

        /**
         * @brief Clears the back buffer with the specified color.
         * @param r Red component (0..1)
         * @param g Green component (0..1)
         * @param b Blue component (0..1)
         */
        void ClearBackBuffer(float r, float g, float b) noexcept;

        /**
         * @brief Updates the view-projection matrix used by the shaders.
         * @param vp ViewProjection matrix
         */
        void SetViewProjection(const Maths::Mat4f& vp);

        /// @brief Returns the D3D11 device
        ID3D11Device* GetDevice() const noexcept { return pDevice.Get(); }

        /// @brief Returns the D3D11 device context
        ID3D11DeviceContext* GetContext() const noexcept { return pContext.Get(); }

        /// @brief Returns the swap chain
        IDXGISwapChain* GetSwapChain() const noexcept { return pSwapChain.Get(); }

        /// @brief Returns the render target view
        ID3D11RenderTargetView* GetRenderTargetView() const noexcept { return pTarget.Get(); }

        /**
         * @brief Draws a mesh using the provided material.
         * @param mesh Mesh asset containing vertex/index buffers
         * @param material Material containing textures and parameters
         */
        void DrawShape(const MeshAsset& mesh, const Material& material);

    private:

        /// Native window handle used for DirectX initialization
        HWND myWindow;

        /// Direct3D device responsible for resource creation
        wrl::ComPtr<ID3D11Device> pDevice = nullptr;

        /// Device context used for rendering commands
        wrl::ComPtr<ID3D11DeviceContext> pContext = nullptr;

        /// Swap chain used to present frames to the screen
        wrl::ComPtr<IDXGISwapChain> pSwapChain = nullptr;

        /// Render target view representing the back buffer
        wrl::ComPtr<ID3D11RenderTargetView> pTarget = nullptr;

        /// Depth stencil buffer used for depth testing
        wrl::ComPtr<ID3D11DepthStencilView> mDepthStencilView;

        /// Sampler state used for texture sampling
        wrl::ComPtr<ID3D11SamplerState> mSampler;

        /// Constant buffer storing object color parameters
        wrl::ComPtr<ID3D11Buffer> mObjectColorBuffer;

        /// Constant buffer storing camera matrices
        wrl::ComPtr<ID3D11Buffer> mMatrixBuffer;

        /// Vertex shader used for rendering meshes
        wrl::ComPtr<ID3D11VertexShader> mVertexShader;

        /// Pixel shader used for fragment shading
        wrl::ComPtr<ID3D11PixelShader>  mPixelShader;

        /// Input layout describing vertex structure
        wrl::ComPtr<ID3D11InputLayout>  mInputLayout;

        /**
         * @brief Searches for available GPU adapters and selects the best one.
         * @return Pointer to the selected adapter
         */
        IDXGIAdapter1* searchForAdapters();

        /**
         * @brief Initializes the swap chain description with desired parameters.
         * @return Configured swap chain description
         */
        DXGI_SWAP_CHAIN_DESC initSwapChainDesc();
    };

} // namespace Engine