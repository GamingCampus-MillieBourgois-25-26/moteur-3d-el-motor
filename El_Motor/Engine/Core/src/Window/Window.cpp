#include "Window/Window.hpp"


namespace Engine
{
	void WindowOpener::WindowInit()
	{
        // Initialize GLFW
        if (!glfwInit()) {
            std::cout << "GLFW Failed to Init\n";
            glfwTerminate();
            return;
        }

        // Récupérer le moniteur principal
        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        if (!primaryMonitor) {
            std::cout << "Failed to get primary monitor\n";
            glfwTerminate();
            return;
        }

        // Récupérer la résolution du moniteur
        const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
        if (!mode) {
            std::cout << "Failed to get video mode\n";
            glfwTerminate();
            return;
        }

        // Créer la fenêtre avec la résolution du moniteur
        window.reset(glfwCreateWindow(mode->width, mode->height, "DX11 ElMotorWindow", nullptr, nullptr));

        if (!window) {
            std::cout << "El Motor EngineWindow failed to load\n";
            glfwTerminate();
            return;
        }

        // Rendre le contexte courant
        glfwMakeContextCurrent(window.get());


	}
}
