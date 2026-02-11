#include "../Core/Headers/CoreEngine/CoreEngine.hpp"

void Engine::CoreEngine::init() {
	// Initialisation des syst�mes de l'Engine , fen�tre, rendu, etc.
	inputManager.init();
	loggerManager.LogInitialize();
	timeManager.Init();
	running = true;
	application.initApp();
}

void Engine::CoreEngine::run() {
	while (running) {
			timeManager.Update();
			float dt = timeManager.GetDeltaTime();
			inputManager.update();
			application.windowOpener->windowPollEvents();
			application.PresentDx();
	}
}

void Engine::CoreEngine::shutdown() {
	// Nettoyage du moteur, lib�ration de m�moires(� faire)
	loggerManager.LogShutdown();
	running = false;
}