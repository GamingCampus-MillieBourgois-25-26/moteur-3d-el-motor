#include "Core/Headers/Time_Manager/TimeManager.hpp"


Engine::TimeManageR::update() {
	static auto lastTime = chrono::high_resolution_clock::now(); // Initialisation de lastTime à la première exécution
	auto currentTime = chrono::high_resolution_clock::now(); // Calcul du temps écoulé depuis la dernière mise à jour
	chrono::duration<float> elapsed = currentTime - lastTime;// Mise à jour de deltaTime avec le temps écoulé en secondes
	deltaTime = elapsed.count();// Mise à jour de lastTime pour la prochaine mise à jour
	lastTime = currentTime;// Mise à jour de totalTime avec le temps écoulé en secondes
}