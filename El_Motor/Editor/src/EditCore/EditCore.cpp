#include "EditCore/EditCore.hpp"
#include "ImGuiLayer/ImGuiLayer.hpp"
#include "GuiToolBarPanel/Buttons.hpp"
#include "External/imgui/includes/CoreIncludes/imgui.h"
#include "External/imgui/includes/backend/imgui_impl_dx11.h"
#include "External/imgui/includes/backend/imgui_impl_glfw.h"

void Editor::EditorCore::editorInit() {
	coreEngine.init();

}

void Editor::EditorCore::editorRun(Engine::Application& app)
{
	coreEngine.run();
	InputUpdate(app);
}



void Editor::EditorCore::editorShutdown() {



}



void Editor::EditorCore::InputUpdate(Engine::Application& app)
{
	auto& input = coreEngine.getInputManager();
	GLFWwindow* window = app.getWindowOpener().getMyWindow();

	// Mise à jour des inputs clavier
	input.updateKey(Engine::KeyCode::Z, glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS);
	input.updateKey(Engine::KeyCode::Q, glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS);
	input.updateKey(Engine::KeyCode::S, glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
	input.updateKey(Engine::KeyCode::D, glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);
	input.updateKey(Engine::KeyCode::ESCAPE, glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
	input.updateKey(Engine::KeyCode::SPACE, glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);


	// Mise à jour des inputs souris
	input.updateMouseButton(Engine::MouseButton::Left, glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
	input.updateMouseButton(Engine::MouseButton::Right, glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
	input.updateMouseButton(Engine::MouseButton::Middle, glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);

	// Mise à jour de la position de la souris
	glfwGetCursorPos(window, &x, &y);
	input.setMousePosition({ (float)getMouseEditorX(), (float)getMouseEditorY() });
}


void  Editor::EditorCore::startRuntime() {



}
