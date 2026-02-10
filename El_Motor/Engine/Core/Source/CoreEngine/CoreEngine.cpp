#include "../Core/Headers/CoreEngine/CoreEngine.hpp"

void Engine::CoreEngine::init() {
	// Initialisation des systèmes de l'Engine , fenêtre, rendu, etc.
	inputManager.init();
	loggerManager.LogInitialize();
	timeManager.Init();
	running = true;
	windowOpener.WindowInit();
}

void Engine::CoreEngine::run() {
	if (running == true) {
		timeManager.Update();
		float dt = timeManager.GetDeltaTime();
		inputManager.update();
		windowOpener.windowPollEvents();
		windowOpener.windowSwapBuffers();
	}
}

void Engine::CoreEngine::shutdown() {
	// Nettoyage du moteur, libération de mémoires(à faire)
	loggerManager.LogShutdown();
	running = false;
}