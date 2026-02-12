#pragma once

#include <chrono>
#include "Logger/Logger.hpp"

namespace Engine
{
	class TimeManager
	{
	public:
		void Init();
		void Update();

		float GetDeltaTime() const;

	private:
		using Clock = std::chrono::high_resolution_clock;

		Clock::time_point lastTime;
		float deltaTime = 0.0f;
	};
}
