#include "../Core/Headers/CoreEngine/CoreEngine.hpp"

void Engine::CoreEngine::init() {
	// Initialisation des systèmes de l'Engine , fenêtre, rendu, etc.
	inputManager.init();
	loggerManager.LogInitialize();
	timeManager.Init();
	running = true;
	application = Application(); // Initialise l'application, qui à son tour initialise la fenêtre et D3D11
}

void Engine::CoreEngine::run() {
	while (running && !glfwWindowShouldClose(application.windowOpener->getMyWindow())) {
			timeManager.Update();
			float dt = timeManager.GetDeltaTime();
			inputManager.update();
			application.windowOpener->windowPollEvents();
			application.windowOpener->windowSwapBuffers();
	}
}

void Engine::CoreEngine::shutdown() {
	// Nettoyage du moteur, libération de mémoires(à faire)
	loggerManager.LogShutdown();
	running = false;
}