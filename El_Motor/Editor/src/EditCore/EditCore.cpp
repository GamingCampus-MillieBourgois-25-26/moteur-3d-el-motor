#include "EditCore/EditCore.hpp"
#include "ImGuiLayer/ImGuiLayer.hpp"
#include "GuiToolBarPanel/Buttons.hpp"
#include "External/imgui/includes/CoreIncludes/imgui.h"
#include "External/imgui/includes/backend/imgui_impl_dx11.h"
#include "External/imgui/includes/backend/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>

void Editor::EditorCore::editorInit(Engine::Application& app) {
	coreEngine.init(app);
}

void Editor::EditorCore::editorRun(Engine::Application& app)
{
	coreEngine.run();
	InputUpdate(app);
	coreEngine.getInputManager().update();
}

void Editor::EditorCore::editorShutdown() {
}

void Editor::EditorCore::InputUpdate(Engine::Application& app)
{
	auto& input = coreEngine.getInputManager();
	GLFWwindow* window = app.getWindowOpener().getMyWindow();

	// Mise à jour des inputs clavier avec scancodes (positions physiques)
	// Fonctionne avec n'importe quelle disposition de clavier (AZERTY, QWERTY, etc.)
	input.updateKey(Engine::Scancode::KEY_W, glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
	input.updateKey(Engine::Scancode::KEY_A, glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
	input.updateKey(Engine::Scancode::KEY_S, glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
	input.updateKey(Engine::Scancode::KEY_D, glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);
	input.updateKey(Engine::Scancode::SPACE, glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);
	input.updateKey(Engine::Scancode::ESCAPE, glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
	input.updateKey(Engine::Scancode::LSHIFT, glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);
	input.updateKey(Engine::Scancode::LCTRL, glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS);

	// Mise à jour des inputs souris
	input.updateMouseButton(Engine::MouseButton::Left, glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
	input.updateMouseButton(Engine::MouseButton::Right, glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
	input.updateMouseButton(Engine::MouseButton::Middle, glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);

	// Mise à jour de la position de la souris
	glfwGetCursorPos(window, &x, &y);
	input.setMousePosition({ (float)getMouseEditorX(), (float)getMouseEditorY() });
	std::cout << input.isKeyHeld(Engine::KeyCode::Z);
}

void Editor::EditorCore::startRuntime() {
}
