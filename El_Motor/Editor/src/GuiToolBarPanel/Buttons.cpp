#include "GuiToolBarPanel/Buttons.hpp"
#include "External/imgui/includes/CoreIncludes/imgui.h"
#include "External/imgui/includes/backend/imgui_impl_dx11.h"
#include "External/imgui/includes/backend/imgui_impl_glfw.h"
#include <iostream>
#include <string>


void Editor::Buttons::init() 
{

}




bool Editor::Buttons::createProject()
{
    if (ImGui::Button("Create Project", ImVec2(200, 50)))
    {
        return true;
    }
    return false;

}

bool Editor::Buttons::loadProject() {

    if (ImGui::Button("Load Project", ImVec2(200, 50)))
    {
        return true;
    }
    return false;

}





bool Editor::Buttons::startRuntime()
{
    if (ImGui::Button("Run", ImVec2(50, 50)))
    {
        return true;
    }
    return false;

}
void Editor::Buttons::selectEntity(Engine::Scene& scene)
{
    ImGui::BeginChild("Hierarchy", ImVec2(250, 0), true);
    auto& currentSelected = scene.GetRootObjects();

    for (int i = 0; i < scene.GetRootObjects().size() ; i++)
    {
       
        Engine::GameObject* go = currentSelected[i];
        if (!go) continue; // skip nullptr



        ImGui::PushID(i);
        std::string label = "Entity " + std::to_string(i); //Name des entité
        bool IsSelected = (selectedEntity == go);


        if (ImGui::Selectable(label.c_str(), IsSelected))//Box qui défile selon le nombre d'entité 
        {
            selectedEntity = go;
        }

        ImGui::PopID();
    }

    ImGui::EndChild();
}

bool Editor::Buttons::changeCmpntValue()
{

    if (ImGui::Button("box trasform", ImVec2(200, 50)))
    {
        return true;
    }
    return false;

}


void Editor::Buttons::createEntity(Engine::Scene& scene)
{
    if (ImGui::Button("create", ImVec2(100, 50)))
    {
        selectedEntity = scene.CreateGameObject();
    }
}

void Editor::Buttons::delEntity(Engine::Scene& scene)
{
    if (ImGui::Button("delete", ImVec2(100, 50)))
    {
        
        scene.DestroyGameObject(selectedEntity);
        selectedEntity = nullptr;
    }
}





