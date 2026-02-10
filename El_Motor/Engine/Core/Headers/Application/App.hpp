#pragma once
#include "../Core/Headers/D3D11/D3D11.hpp"
#include "../Core/Headers/Window/Window.hpp"


namespace Engine {

	class Application {
	private:
		std::unique_ptr<D3D11> d3d11;

	public:
		std::unique_ptr<WindowOpener> windowOpener;
		Application();
		D3D11* getD3D11() { return d3d11.get(); } // Récupère le pointeur brut de D3D11 pour l'utiliser dans d'autres parties du moteur
	};
}