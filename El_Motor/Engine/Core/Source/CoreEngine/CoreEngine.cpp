#include "Core/Headers/CoreEngine/CoreEngine.hpp"

Engine::CoreEngine::init() {
	// Initialisation des systèmes de l'Engine , fenêtre, rendu, etc.
	running = true;
}

Engine::CoreEngine::run() {
	while (running) {
		timeManager.update();
		inputManager.update();
		currentScene.update(timeManager.deltaTime);
		currentScene.render(); 
	}
}

Engine::CoreEngine::shutdown() {
	// Nettoyage du moteur, libération de mémoires
	running = false;
}