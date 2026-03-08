#pragma once
#include "External/imgui/includes/CoreIncludes/imgui.h"
#include "External/imgui/includes/backend/imgui_impl_dx11.h"
#include "External/imgui/includes/backend/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include <d3d11.h>

/**
 * @brief Class responsible for managing the GUI layer using ImGui.
 *
 * Handles initialization, frame management, and rendering
 * of the graphical user interface with DirectX11 and GLFW.
 */
class GuiLayer
{
public:
    /**
     * @brief Default constructor
     */
    GuiLayer() = default;

    /**
     * @brief Destructor
     */
    ~GuiLayer() = default;

    /**
     * @brief Initializes the ImGui GUI layer with the required rendering context.
     *
     * @param window Pointer to the GLFW window
     * @param device DirectX11 device used for rendering
     * @param context DirectX11 device context
     * @param rtv Render target view used for GUI rendering
     */
    void Init(GLFWwindow* window, ID3D11Device* device, ID3D11DeviceContext* context, ID3D11RenderTargetView* rtv);

    /**
     * @brief Begins a new ImGui frame.
     *
     * Must be called before drawing any GUI elements.
     */
    void BeginFrame();

    /**
     * @brief Ends the ImGui frame and renders all GUI elements.
     */
    void EndFrame();

    /**
     * @brief Clears the render target with a specific color.
     *
     * @param r Red color component
     * @param g Green color component
     * @param b Blue color component
     * @param a Alpha color component
     */
    void Clear(float r, float g, float b, float a);

private:
    /// @brief Pointer to the GLFW window used by the GUI
    GLFWwindow* m_Window = nullptr;

    /// @brief DirectX11 device used for rendering
    ID3D11Device* m_Device = nullptr;

    /// @brief DirectX11 device context used to issue rendering commands
    ID3D11DeviceContext* m_Context = nullptr;

    /// @brief Render target view used by DirectX11 to render the GUI
    ID3D11RenderTargetView* m_RTV = nullptr;
};