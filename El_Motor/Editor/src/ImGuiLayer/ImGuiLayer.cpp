#include "ImGuiLayer/ImGuiLayer.hpp"
#include "D3D11/D3D11.hpp"
#include "External/imgui/includes/CoreIncludes/imgui.h"
#include "External/imgui/includes/backend/imgui_impl_dx11.h"
#include "External/imgui/includes/backend/imgui_impl_glfw.h"



	void Editor::ImGuiLayer::Init(GLFWwindow* window,
		ID3D11Device* device,
		ID3D11DeviceContext* context)
	{

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOther(window, true);
		ImGui_ImplDX11_Init(device, context);



	}

	void Editor::ImGuiLayer::Begin()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Editor::ImGuiLayer::End()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}

	void Editor::ImGuiLayer::Shutdown()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}