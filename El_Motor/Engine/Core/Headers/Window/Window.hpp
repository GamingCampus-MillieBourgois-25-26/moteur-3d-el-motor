#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <memory>

namespace Engine
{
	class WindowOpener {
	private:
		const int WIDTH = 800, HEIGHT = 600;
		std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window{ nullptr, glfwDestroyWindow };

	public:

		void WindowInit(); // Initialisation de la fenêtre
		void windowPollEvents() { glfwPollEvents(); } // Récupère les événements de la fenêtre via GLFW
		void windowSwapBuffers() { glfwSwapBuffers(window.get()); } // Affiche le contenu rendu à l'écran en échangeant les buffers entre le back buffer et le front buffer

		GLFWwindow* getMyWindow() { return window.get(); } // récupere le pointeur brut de la fenêtre pour l'utiliser plus tard

	};
}
