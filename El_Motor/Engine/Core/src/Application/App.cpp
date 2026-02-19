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

			ShapeData triangle;
			triangle.vertices = {
				{-0.8f,  0.6f, 0,0,0},  // v0
				{ 0.8f,  0.6f, 0,0,0},  // v1
				{-0.6f,  0.0f, 0,0,0},  // v2
				{ 0.6f,  0.0f, 0,0,0},  // v3
				{-0.4f, -0.6f, 0,0,0},  // v4
				{ 0.4f, -0.6f, 0,0,0}   // v5
			};
			triangle.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;


			d3d11->ClearBackBuffer(0.f, 0.f, 1.f); // Nettoie le back buffer avec une couleur grise (à modifier)
			d3d11->DrawShape(triangle); // Dessine un triangle de test (à remplacer par le rendu réel du moteur)
			d3d11->Present(); // Appelle la méthode Present de D3D11 pour présenter le swap chain à l'écran
		}
	}
}