#include "InputBridge/InputBridge.hpp"
#include "Input_Manager/InputManager.hpp"


void Runtime::InputBridge::init() {

}

void Runtime::InputBridge::update(Engine::CoreEngine& core, Engine::Application& app) {
	fetchGLFWInput(core,app);
}

void Runtime::InputBridge::fetchGLFWInput(Engine::CoreEngine& core, Engine::Application& app) {
	auto& input = core.getInputManager();
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
	input.setMousePosition({ (float)x,(float)y });
}