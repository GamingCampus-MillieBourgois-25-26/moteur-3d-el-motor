#include "MainBridge/Bridge.hpp"


void Runtime::Bridge::init() {
	engine.init();
}

void Runtime::Bridge::run() {
	// La boucle principale , elle continue tant que le moteur est en cours d'exécution et que la fenêtre n'est pas fermée(pas de fermeture de la fenêtre dispo pour le moment)
	while (engine.isRunning() && engine.shouldClose()) {
		engine.run();
		inputBridge.update(engine);
	}
	shutdown();
}
void Runtime::Bridge::shutdown() {
	engine.shutdown();
}