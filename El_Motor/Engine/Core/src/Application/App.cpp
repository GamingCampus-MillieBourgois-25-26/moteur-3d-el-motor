#include "Application/App.hpp"

namespace Engine
{
	Application::Application() {
		windowOpener = std::make_unique<WindowOpener>(); // Crée une instance de WindowOpener
		windowOpener->WindowInit(); // Initialise la fenêtre
		d3d11 = std::make_unique<D3D11>(windowOpener->getMyWindow()); // Crée une instance de D3D11 en passant le pointeur de la fenêtre
	}
}