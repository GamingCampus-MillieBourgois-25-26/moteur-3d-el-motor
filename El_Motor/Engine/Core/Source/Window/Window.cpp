#include "../Core/Headers/Window/Window.hpp"


namespace Engine
{
	void WindowOpener::WindowInit()
	{
		// Initialize GLFM
		if (!glfwInit()) {
			std::cout << "GLFW Failed to Init" << "\n";
			glfwTerminate();
			return;
		}

		window.reset(glfwCreateWindow(WIDTH, HEIGHT, "DX11 ElMotorWindow", NULL, NULL));

		if (!window) {
			std::cout << "El Motor EngineWindow failed to load";
			glfwTerminate();
			return;
		}
	}

}
