#include "EditCore/EditCore.hpp"
#include "ImGuiLayer/ImGuiLayer.hpp"
#include "GuiToolBarPanel/Buttons.hpp"
#include "External/imgui/includes/CoreIncludes/imgui.h"
#include "External/imgui/includes/backend/imgui_impl_dx11.h"
#include "External/imgui/includes/backend/imgui_impl_glfw.h"

void Editor::EditorCore::editorInit() {
	coreEngine.init();

}

void Editor::EditorCore::editorRun()
{
	coreEngine.run();
}



void Editor::EditorCore::editorShutdown() {



}

void Editor::EditorCore::DrawUi()
{

}
