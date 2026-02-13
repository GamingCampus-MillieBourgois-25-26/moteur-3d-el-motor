#pragma once
#include <iostream>
#define GLFW_EXPOSE_NATIVE_WIN32 // permet le glfwGetWin32Window() d'être défini
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

		void WindowInit(); // Initialisation de la fenêtre

		void* GetNativeWindow() const override { return glfwGetWin32Window(window.get()); }
		void windowPollEvents() override { glfwPollEvents(); } // Récupère les événements de la fenêtre via GLFW

		GLFWwindow* getMyWindow() const { return window.get(); } // récupere le pointeur brut de la fenêtre pour l'utiliser plus tard

	};
}
