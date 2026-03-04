#pragma once
#include <iostream>
#define GLFW_EXPOSE_NATIVE_WIN32 // permet le glfwGetWin32Window() d'etre d�fini
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <memory>

#include "IWindow.hpp"

namespace Engine
{
	class WindowOpener : public IWindow {
	private:
		const int WIDTH = 800;
		const int HEIGHT = 600;

		std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window{ nullptr, glfwDestroyWindow };

	public:
		void WindowInit();
		void* GetNativeWindow() const override { return glfwGetWin32Window(window.get()); }
		void windowPollEvents() override { glfwPollEvents(); } // Recupere les evenements de la fenetre via GLFW

		bool shouldClose() const { return glfwWindowShouldClose(window.get()); }

		GLFWwindow* getMyWindow() const { return window.get(); } // recupere le pointeur brut de la fenetre pour l'utiliser plus tard

	};
}