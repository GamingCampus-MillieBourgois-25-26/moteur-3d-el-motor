#include <iostream>

#include "../Core/Headers/CoreEngine/CoreEngine.hpp"
#include "../Core/Headers/D3D11/D3D11.hpp"

int main() {
	Engine::CoreEngine engine;
	engine.init();
	engine.run(); // Libérer la mémoire

}