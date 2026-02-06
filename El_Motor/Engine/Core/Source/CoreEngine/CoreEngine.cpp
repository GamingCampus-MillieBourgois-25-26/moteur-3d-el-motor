#include "../Core/Headers/CoreEngine/CoreEngine.hpp"

void Engine::CoreEngine::init() {
	// Initialisation des systèmes de l'Engine , fenêtre, rendu, etc.
	inputManager.init();
	running = true;
}

void Engine::CoreEngine::run() {
	while (running) {
		timeManager.update();
		inputManager.update();
	}
}

void Engine::CoreEngine::shutdown() {
	// Nettoyage du moteur, libération de mémoires(à faire)
	running = false;
}