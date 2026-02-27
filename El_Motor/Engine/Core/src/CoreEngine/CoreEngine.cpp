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
		SetDeltaTime(timeManager.GetDeltaTime());
		inputManager.update();
		getScene()->Update(getDeltaTime());
}

void Engine::CoreEngine::shutdown() {
	// Nettoyage du moteur, lib�ration de m�moires(� faire)
	loggerManager.LogShutdown();
	running = false;
}