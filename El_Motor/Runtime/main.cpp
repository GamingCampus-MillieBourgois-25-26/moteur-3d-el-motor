#include <iostream>

#include "../Core/Headers/CoreEngine/CoreEngine.hpp"

int main() {
	Engine::CoreEngine engine;
	engine.init();
	engine.run(); // Libérer la mémoire
}