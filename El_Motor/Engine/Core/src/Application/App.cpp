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
			d3d11->ClearBackBuffer(0.f, 0.f, 1.f); // Nettoie le back buffer avec une couleur grise (à modifier)
			d3d11->DrawTriangleTest(); // Dessine un triangle de test (à remplacer par le rendu réel du moteur)
			d3d11->Present(); // Appelle la méthode Present de D3D11 pour présenter le swap chain à l'écran
		}
	}
}