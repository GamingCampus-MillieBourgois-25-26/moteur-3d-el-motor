#include "../Runtime/EngineBridge/Header/MainBridge/Bridge.hpp"


int main() {
	Runtime::Bridge bridge;
	bridge.init();
	bridge.run();
}