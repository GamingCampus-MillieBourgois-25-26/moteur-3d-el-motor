#include "../Core/Headers/Window/Window.hpp"

//void WindowOpener::WindowDisplay()
//{
//	//WindowInit();
//	//WindowRenderer();
//}

//void WindowOpener::WindowInit()
//{
//	// Initialize GLFM
//	if (!glfwInit()) {
//		std::cout << "GLFW Failed to Init" << "\n";
//		glfwTerminate();
//		return;
//	}
//
//	window.reset(glfwCreateWindow(WIDTH, HEIGHT, "DX11 ElMotorWindow", NULL, NULL));
//	//GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "El Motor EngineWindow", NULL, NULL);
//
//	if (!window) {
//		std::cout << "El Motor EngineWindow failed to load";
//		glfwTerminate();
//		return;
//	}
//}
//
//void WindowOpener::WindowRenderer()
//{
//	//Get frame buffer size
//	int bufferWidth, bufferHeight;
//	glfwGetFramebufferSize(getMyWindow(), &bufferWidth, &bufferHeight);
//
//	//MainLoop 
//	while (!glfwWindowShouldClose(getMyWindow()))
//	{
//		//Get user input
//		glfwPollEvents();
//	}
//}


void WindowOpener::test() {
	std::cout << "test";
}