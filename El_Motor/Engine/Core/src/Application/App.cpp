#include "Application/App.hpp"


namespace Engine
{
	void Application::initApp() {
		windowOpener = std::make_unique<WindowOpener>(); // Crée une instance de WindowOpener
		windowOpener->WindowInit(); // Initialise la fenêtre
		d3d11 = std::make_unique<D3D11>(*windowOpener); // Crée une instance de D3D11 en passant le pointeur de la fenêtre

	}

	void Application::PresentDx() {
		if (d3d11) {
			// Ici ajout des appels pour dessiner les formes ou objets 3D en utilisant d3d11->DrawShape() 
		}
	}
}