#include "CoreEngine/CoreEngine.hpp"

void Engine::CoreEngine::init(Engine::Application& app) {
	// Initialisation des syst�mes de l'Engine , fen�tre, rendu, etc.
	inputManager.init();
	loggerManager.LogInitialize();
	timeManager.Init();
	assetManager.Initialize(app.getD3D11()->GetDevice(), app.getD3D11()->GetContext());

	running = true;

}

void Engine::CoreEngine::run() {
		timeManager.Update();
		SetDeltaTime(timeManager.GetDeltaTime());
		inputManager.update();
		getCamera().Update(inputManager);
		getScene()->Update(getDeltaTime());
}

void Engine::CoreEngine::shutdown() {
	// Nettoyage du moteur, lib�ration de m�moires(� faire)
	loggerManager.LogShutdown();
	running = false;
}