#pragma once
#include <iostream>
//#include <GLFW/glfw3.h>
#include <memory>

class WindowOpener {
private :
	const int WIDTH = 800, HEIGHT = 600;
	//std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window{ nullptr, glfwDestroyWindow };

public:

	void WindowDisplay();
	void WindowInit();
	void WindowRenderer();
	//GLFWwindow* getMyWindow() { return window.get(); }

	void test();
};
