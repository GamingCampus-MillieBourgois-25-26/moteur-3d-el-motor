#include "../Core/Headers/CoreEngine/CoreEngine.hpp"

void Engine::CoreEngine::init() {
	// Initialisation des systèmes de l'Engine , fenêtre, rendu, etc.
	running = true;
}

void Engine::CoreEngine::run() {
	while (running) {
		timeManager.update();
		inputManager.update();
		//currentScene.update(timeManager.deltaTime);
		//currentScene.render(); 
	}
}

void Engine::CoreEngine::shutdown() {
	// Nettoyage du moteur, libération de mémoires
	running = false;
}