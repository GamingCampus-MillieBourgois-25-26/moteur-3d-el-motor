#include "HubManager/HubManager.hpp"
#include "Scene/Scene.hpp"
#include "GuiToolBarPanel/Buttons.hpp"


Editor::HubManager::HubManager()
{

}

Editor::HubManager::~HubManager()
{

}

void Editor::HubManager::Init()
{
	guiLayer.Init(app.getWindowOpener().getMyWindow(),app.getD3D11()->GetDevice(),app.getD3D11()->GetContext());
}

void Editor::HubManager::CreateProject()
{
	std::unique_ptr<Engine::Scene> scene = std::make_unique<Engine::Scene>();
}

void Editor::HubManager::LoadProject()
{

}