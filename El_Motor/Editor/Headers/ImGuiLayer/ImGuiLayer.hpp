#pragma once
#include "External/imgui/includes/CoreIncludes/imgui.h"
#include "External/imgui/includes/backend/imgui_impl_dx11.h"
#include "External/imgui/includes/backend/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include <d3d11.h>

/// <summary>
/// Class responsible for managing the GUI layer using ImGui.
/// Handles initialization, frame management, and rendering
/// of the graphical user interface with DirectX11 and GLFW.
/// </summary>
class GuiLayer
{
public:

    /// <summary>
    /// Default constructor
    /// </summary>
    GuiLayer() = default;

    /// <summary>
    /// Destructor
    /// </summary>
    ~GuiLayer() = default;

    /// <summary>
    /// Initializes the ImGui GUI layer with the required rendering context.
    /// </summary>
    /// <param name="window">Pointer to the GLFW window</param>
    /// <param name="device">DirectX11 device used for rendering</param>
    /// <param name="context">DirectX11 device context</param>
    /// <param name="rtv">Render target view used for GUI rendering</param>
    void Init(GLFWwindow* window, ID3D11Device* device, ID3D11DeviceContext* context, ID3D11RenderTargetView* rtv);

    /// <summary>
    /// Begins a new ImGui frame.
    /// Must be called before drawing any GUI elements.
    /// </summary>
    void BeginFrame();

    /// <summary>
    /// Ends the ImGui frame and renders all GUI elements.
    /// </summary>
    void EndFrame();

    /// <summary>
    /// Clears the render target with a specific color.
    /// </summary>
    /// <param name="r">Red color component</param>
    /// <param name="g">Green color component</param>
    /// <param name="b">Blue color component</param>
    /// <param name="a">Alpha color component</param>
    void Clear(float r, float g, float b, float a);

private:

    /// Pointer to the GLFW window used by the GUI
    GLFWwindow* m_Window = nullptr;

    /// DirectX11 device used for rendering
    ID3D11Device* m_Device = nullptr;

    /// DirectX11 device context used to issue rendering commands
    ID3D11DeviceContext* m_Context = nullptr;

    /// Render target view used by DirectX11 to render the GUI
    ID3D11RenderTargetView* m_RTV = nullptr;
};