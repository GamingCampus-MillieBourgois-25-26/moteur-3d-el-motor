#include "MainBridge/Bridge.hpp"


void Runtime::Bridge::init() {
	app.initApp();
	engine.init();

}

void Runtime::Bridge::run() {
	// La boucle principale , elle continue tant que le moteur est en cours d'exécution et que la fenêtre n'est pas fermée(pas de fermeture de la fenêtre dispo pour le moment)
	while (engine.isRunning() && shouldClose() && !app.getWindowOpener().shouldClose()) {
		app.windowOpener->windowPollEvents();
		app.PresentDx();
		engine.run();
		inputBridge.update(engine,app);
	}
	shutdown();
}
void Runtime::Bridge::shutdown() {
	engine.shutdown();
}