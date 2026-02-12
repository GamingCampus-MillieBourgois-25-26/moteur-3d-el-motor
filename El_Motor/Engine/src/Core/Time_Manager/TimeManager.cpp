#include "Core/Time_Manager/TimeManager.hpp"

#include <chrono>
#include <string>

#include "Core/Logger/Logger.hpp"

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

    // Clamp du deltaTime empeche les frame drops extr�mes qui pourraient causer des probl�mes sur le jeu
    const float maxDelta = 0.1f;
    if (deltaTime > maxDelta)
        deltaTime = maxDelta;

    lastTime = currentTime;

    if (deltaTime > maxDelta)
    {
        Engine::LoggerManager::Get().LogWarning("DeltaTime spike detected: " + std::to_string(deltaTime));
        deltaTime = maxDelta;
    }
}

float Engine::TimeManager::GetDeltaTime() const
{
    return deltaTime;
}
