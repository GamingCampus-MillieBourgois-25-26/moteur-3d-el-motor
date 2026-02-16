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

bool Editor::Buttons::showEntity()
{
    if (ImGui::Button("show", ImVec2(200, 50)))
    {
        return true;
    }
    return false;
}

void Editor::Buttons::selectEntity(Engine::Scene& scene)
{
    ImGui::BeginChild("Hierarchy", ImVec2(250, 10), true);

    for (int i = 0; i < /*scene.GetRootObjects().size()*/ ; i++)
    {
        ImGui::PushID(i);

        ImGui::SameLine();
        std::string label = "Entity " + std::to_string(i);
        // Sélection
        bool isSelected = (selectedEntity == i);
       /* if (ImGui::Selectable(label.c_str(), isSelected))//Box qui défile selon le nombre d'entité 
        {
            selectedEntity = i;
        }*/

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
        scene.CreateGameObject();
    }
}

void Editor::Buttons::delEntity(Engine::Scene& scene)
{
    if (ImGui::Button("delete", ImVec2(100, 50)))
    {
        scene.DestroyGameObject(scene.GetRootObjects()[selectedEntity]);
    }
}


