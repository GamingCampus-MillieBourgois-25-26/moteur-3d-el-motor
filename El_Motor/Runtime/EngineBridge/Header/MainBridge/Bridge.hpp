#include "../../Runtime/EngineBridge/Header/InputBridge/InputBridge.hpp"

namespace Runtime
{
	class Bridge {
	public:
		void init();
		void run();
		void shutdown();

	private:

		Engine::CoreEngine engine;
		Runtime::InputBridge inputBridge;
	};
}

