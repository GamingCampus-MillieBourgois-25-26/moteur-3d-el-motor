#include "InputBridge/InputBridge.hpp"
#include "Input_Manager/InputManager.hpp"


void Runtime::InputBridge::init() {

}

void Runtime::InputBridge::update(Engine::CoreEngine& core) {
	fetchGLFWInput(core);
}

void Runtime::InputBridge::fetchGLFWInput(Engine::CoreEngine& core) {

	auto& input = core.getInputManager();
	GLFWwindow* window = core.getWindowOpener().getMyWindow();

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
	input.setMousePosition({ (float)getMouseX(), (float)getMouseY()});
}