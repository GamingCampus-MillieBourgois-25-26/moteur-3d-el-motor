#include "../Core/Headers/CoreEngine/CoreEngine.hpp"

namespace Runtime
{

	class InputBridge {
	public:

		void init();
		void update(Engine::CoreEngine& core);
		void fetchGLFWInput(Engine::CoreEngine& core);



		// Méthodes pour get les coordonnées de la souris
		double getMouseX() const { return x; }
		double getMouseY() const { return y; }


	protected:

		// Variables pour stocker les coordonnées de la souris
		double x = 0.0;
		double y = 0.0;

	};
}