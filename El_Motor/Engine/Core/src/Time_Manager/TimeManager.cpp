#include "Time_Manager/TimeManager.hpp"
#include "Logger/Logger.hpp"

void Engine::TimeManager::Init()
{
	lastTime = Clock::now();
	deltaTime = 0.0f;
}

void Engine::TimeManager::Update()
{
    auto currentTime = Clock::now();
    std::chrono::duration<float> elapsed = currentTime - lastTime;

    deltaTime = elapsed.count();
    lastTime = currentTime;

    const float maxDelta = 0.1f;

    if (deltaTime > maxDelta)
    {
        Engine::LoggerManager::Get().LogWarning(
            "DeltaTime spike detected: " + std::to_string(deltaTime)
        );

        deltaTime = maxDelta;
    }

    fps = 0.9f * fps + 0.1f * (1.0f / deltaTime);
}

float Engine::TimeManager::GetDeltaTime() const
{
	return deltaTime;
}
