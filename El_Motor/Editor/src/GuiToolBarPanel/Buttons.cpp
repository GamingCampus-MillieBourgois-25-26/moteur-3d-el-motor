#include "ImGuiButtons/Buttons.hpp"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include <d3d11.h>
#include "Window/Window.hpp"



void Editor::Buttons::init() {



}


void Editor::Buttons::startRuntime() {

	ImGui::Begin();

	if (ImGui::Button("Run"))
	{
		startRuntime();
	}

	ImGui::End();

}

void Editor::Buttons::selectEntity() {




}
void Editor::Buttons::changeCmpntValue() {



}