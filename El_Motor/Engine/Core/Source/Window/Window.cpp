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

	void WindowOpener::WindowRender()
	{
		// Get frame buffer size
		int bufferWidth, bufferHeight;
		glfwGetFramebufferSize(getMyWindow(), &bufferWidth, &bufferHeight);

		// Main loop
		while (!glfwWindowShouldClose(getMyWindow()))
		{
			// Get user input
			glfwPollEvents();
		}
	}

}
