#include "../Core/Headers/Time_Manager/TimeManager.hpp"

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

	// Clamp du deltaTime empeche les frame drops extrêmes qui pourraient causer des problèmes sur le jeu
	const float maxDelta = 0.1f;
	if (deltaTime > maxDelta)
		deltaTime = maxDelta;

	lastTime = currentTime;

	if (deltaTime > maxDelta)
	{
		Engine::LoggerManager::Get().LogWarning
		(
			"DeltaTime spike detected: " + std::to_string(deltaTime)
		);
		deltaTime = maxDelta;
	}


}

float Engine::TimeManager::GetDeltaTime() const
{
	return deltaTime;
}
