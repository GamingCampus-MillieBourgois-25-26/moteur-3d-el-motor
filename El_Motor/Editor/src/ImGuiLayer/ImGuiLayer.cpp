#include "ImGuiLayer/ImGuiLayer.hpp"

void GuiLayer::Init(GLFWwindow* window, ID3D11Device* device, ID3D11DeviceContext* context, ID3D11RenderTargetView* rtv)
{
    m_Window = window;
    m_Device = device;
    m_Context = context;
    m_RTV = rtv;

    // Initialisation ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // clavier
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // docking si version récente
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // multi-viewport

    ImGui::StyleColorsDark();

    // Initialisation backends 
    ImGui_ImplGlfw_InitForOther(window, true); // GLFW
    ImGui_ImplDX11_Init(device, context);      // DX11
}

void GuiLayer::BeginFrame()
{
    // Bind le render target
    m_Context->OMSetRenderTargets(1, &m_RTV, nullptr);

    // Commence une nouvelle frame ImGui
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GuiLayer::EndFrame()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Si multi-viewport
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void GuiLayer::Clear(float r, float g, float b, float a)
{
    // Clear le render target avec la couleur passée
    float clearColor[4] = { r, g, b, a };
    m_Context->ClearRenderTargetView(m_RTV, clearColor);
}