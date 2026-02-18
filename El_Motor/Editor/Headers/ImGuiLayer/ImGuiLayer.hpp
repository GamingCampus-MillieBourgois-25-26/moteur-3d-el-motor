#pragma once
#include "External/imgui/includes/CoreIncludes/imgui.h"
#include "External/imgui/includes/backend/imgui_impl_dx11.h"
#include "External/imgui/includes/backend/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include <d3d11.h>

class GuiLayer
{
public:
    GuiLayer() = default;
    ~GuiLayer() = default;

    void Init(GLFWwindow* window, ID3D11Device* device, ID3D11DeviceContext* context, ID3D11RenderTargetView* rtv);
    void BeginFrame();
    void EndFrame();

    void Clear(float r, float g, float b, float a);

private:
    GLFWwindow* m_Window = nullptr;
    ID3D11Device* m_Device = nullptr;
    ID3D11DeviceContext* m_Context = nullptr;
    ID3D11RenderTargetView* m_RTV = nullptr;
};