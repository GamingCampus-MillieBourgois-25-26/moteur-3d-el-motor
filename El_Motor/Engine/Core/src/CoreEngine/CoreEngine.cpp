#include "CoreEngine/CoreEngine.hpp"

void Engine::CoreEngine::init(Engine::Application& app) {
	// Initialisation des systemes de l'Engine , fenetre, rendu, etc.
	inputManager.init();
	loggerManager.LogInitialize();
	timeManager.Init();
	assetManager.Initialize(app.getD3D11()->GetDevice(), app.getD3D11()->GetContext());
	// physicSystem.Init();

	running = true;

}

void Engine::CoreEngine::run() {
		timeManager.Update();
		SetDeltaTime(timeManager.GetDeltaTime());
		inputManager.update();
		getScene()->Update(getDeltaTime());
}

void Engine::CoreEngine::shutdown() {
	// Nettoyage du moteur, liberation de memoires(a faire)
	loggerManager.LogShutdown();
	// physicSystem.OnEnd(getScene());
	// physicSystem.Exit();
	running = false;
}