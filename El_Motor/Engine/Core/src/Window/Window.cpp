#include "Window/Window.hpp"


namespace Engine
{
	void WindowOpener::WindowInit()
	{
        if (!glfwInit()) {
            std::cout << "GLFW Failed to Init\n";
            glfwTerminate();
            return;
        }

        // Récupérer le moniteur principal
        GLFWmonitor* primary = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(primary);

        // Mettre la taille de la fenêtre sur la résolution du moniteur
        int WIDTH = mode->width;
        int HEIGHT = mode->height;

        // Créer la fenêtre
        window.reset(glfwCreateWindow(WIDTH, HEIGHT, "DX11 ElMotorWindow", NULL, NULL));

        if (!window) {
            std::cout << "El Motor EngineWindow failed to load";
            glfwTerminate();
            return;
        }

        // Placer la fenêtre au centre (optionnel si fenêtré)
        glfwSetWindowPos(window.get(), 0, 0);

	}
}
