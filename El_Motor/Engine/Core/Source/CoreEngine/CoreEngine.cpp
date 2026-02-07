#include "../Core/Headers/CoreEngine/CoreEngine.hpp"

void Engine::CoreEngine::init() {
	// Initialisation des systèmes de l'Engine , fenêtre, rendu, etc.
	inputManager.init();
	running = true;
	windowOpener.WindowInit();
}

void Engine::CoreEngine::run() {
	while (running && !glfwWindowShouldClose(windowOpener.getMyWindow())) {
			timeManager.update();
			inputManager.update();
			windowOpener.windowPollEvents();
			windowOpener.windowSwapBuffers();
	}
}

void Engine::CoreEngine::shutdown() {
	// Nettoyage du moteur, libération de mémoires(à faire)
	running = false;
}