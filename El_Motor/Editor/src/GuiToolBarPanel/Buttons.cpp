#include "GuiToolBarPanel/Buttons.hpp"
#include "External/imgui/includes/CoreIncludes/imgui.h"
#include "External/imgui/includes/backend/imgui_impl_dx11.h"
#include "External/imgui/includes/backend/imgui_impl_glfw.h"



void Editor::Buttons::init() 
{

}




bool Editor::Buttons::CreateProject()
{
    if (ImGui::Button("Create Project", ImVec2(200, 50)))
    {
        return true;
    }
    return false;

}

bool Editor::Buttons::LoadProject() {

    if (ImGui::Button("Load Project", ImVec2(200, 50)))
    {
        return true;
    }
    return false;

}





bool Editor::Buttons::startRuntime()
{
    if (ImGui::Button("Run", ImVec2(200, 50)))
    {
        return true;
    }
    return false;

}


void Editor::Buttons::selectEntity() 
{

}

void Editor::Buttons::changeCmpntValue() 
{



}

void Editor::Buttons::ShowEntity()
{

}

void Editor::Buttons::ManageEntity()
{

}
