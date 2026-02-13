#include "HubManager/HubManager.hpp"
#include "Scene/Scene.hpp"

HubManager::HubManager()
{
}

HubManager::~HubManager()
{
}

void HubManager::Init()
{
	
}

void HubManager::CreateScene()
{
	std::unique_ptr<Engine::Scene> scene = std::make_unique<Engine::Scene>();
}

void HubManager::LoadScene()
{

}