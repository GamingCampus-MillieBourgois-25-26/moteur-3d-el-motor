#include "CoreEngine/CoreEngine.hpp"

void Engine::CoreEngine::init() {
	// Initialisation des syst�mes de l'Engine , fen�tre, rendu, etc.
	inputManager.init();
	loggerManager.LogInitialize();
	timeManager.Init();
	

	running = true;

}

void Engine::CoreEngine::run() {
		timeManager.Update();
		float dt = timeManager.GetDeltaTime();
		inputManager.update();
		getCamera().Update(inputManager);
		getScene()->Update(dt);
}

void Engine::CoreEngine::shutdown() {
	// Nettoyage du moteur, lib�ration de m�moires(� faire)
	loggerManager.LogShutdown();
	running = false;
}