#pragma once
#include "InputBridge/InputBridge.hpp"
#include "CoreEngine/CoreEngine.hpp"
#include "Application/App.hpp"

namespace Runtime
{
	class Bridge {
	private:
		Engine::Application app;
		Engine::CoreEngine engine;
		Runtime::InputBridge inputBridge;
	public:
		void init();
		void run();
		void shutdown();
		bool shouldClose() const { return app.windowOpener->getMyWindow(); } // vérifie si la fenêtre doit se fermer


	};
}

