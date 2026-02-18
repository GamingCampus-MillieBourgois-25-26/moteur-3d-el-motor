#include "GuiToolBarPanel/Buttons.hpp"
#include "External/imgui/includes/CoreIncludes/imgui.h"
#include "External/imgui/includes/backend/imgui_impl_dx11.h"
#include "External/imgui/includes/backend/imgui_impl_glfw.h"
#include "External/ImGuiFileLog/includes/coreIncludes/ImGuiFileDialog.h"
#include "Assets/MeshAsset/MeshAsset.hpp"
#include "Logger/Logger.hpp"
#include <iostream>



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

void Editor::Buttons::loadAssets(AssetManager& manager)
{

        IGFD::FileDialogConfig config;
        config.path = "Assets";

        ImGuiFileDialog::Instance()->OpenDialog(
            "LoadAssetKey",
            "Choose Asset",
            ".png,.jpg,.obj,.fbx",
            config
        );

        if (ImGuiFileDialog::Instance()->Display("LoadAssetKey"))
        {



            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePath =
                    ImGuiFileDialog::Instance()->GetFilePathName();

                std::string extension =
                    std::filesystem::path(filePath).extension().string();

                if (extension == ".png" || extension == ".jpg")
                {
                    std::cout << "asset loaded" << std::endl;
                }
                else if (extension == ".obj" || extension == ".fbx")
                {
                    manager.Load<MeshAsset>(filePath);
                    std::cout << "ok load";
                }
                else
                {
                    Engine::LoggerManager::Get().LogError(
                        "Unsupported asset type : " + extension
                    );
                }
            }

            ImGuiFileDialog::Instance()->Close();
        }
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
            currentEntityLabel = label;
			selectedComponent = nullptr;
        }

        ImGui::PopID();
    }

    ImGui::EndChild();
}

void Editor::Buttons::showCmpnt(Engine::Scene& scene)
{
    if (!selectedEntity)
        return;

    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(500, 0)); 

    const std::string windowName = "Components";
	ImGui::Begin(windowName.c_str(), nullptr, ImGuiWindowFlags_NoResize);

  

	ImGui::BeginChild("ComponentList", ImVec2(0, 0), true);//Component list child
	addComponent();//Button to add component to the selected entity

    auto& components = selectedEntity->GetAllComponents();

    for (size_t i = 0; i < components.size(); i++)
    {
        Engine::Component* comp = components[i];
        if (!comp) continue;

        ImGui::PushID(comp);

        std::string label = "Component " + std::to_string(i);

        bool isSelected = (selectedComponent == comp);

        if (ImGui::Selectable(label.c_str(), isSelected))
        {
            selectedComponent = comp;
        }

        ImGui::PopID();
		editComponent();//Show the component's editable properties if it's selected
    }

    ImGui::EndChild();
    ImGui::End();
}

void Editor::Buttons::addComponent()
{
    if (!selectedEntity)
        return;

    static int currentItem = 0;

	const char* items[] = { "MeshRenderer", "Camera", "Light" };//List of component types to add
    const int itemCount = IM_ARRAYSIZE(items);

	if (ImGui::BeginCombo("Component Type", items[currentItem]))//Combo box to select component type
    {
        for (int i = 0; i < itemCount; i++)
        {
            bool isSelected = (currentItem == i);

            if (ImGui::Selectable(items[i], isSelected))
                currentItem = i;

            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    ImGui::SameLine();

	if (ImGui::Button("Add")) //Button to add the selected component type to the selected entity
    {
        switch (currentItem)
        {
        case 0: /* Add MeshRenderer */ break;
        case 1: /* Add Camera */ break;
        case 2: /* Add Light */ break;
        }
    }
    delComponent();
}

void Editor::Buttons::delComponent()
{
    if (selectedEntity->GetComponent<Engine::Transform>() != selectedComponent && selectedComponent && ImGui::Button("del"))
    {
		//fonction pour del selectedComponent;
		
	}
}

void Editor::Buttons::editComponent()
{
    if (!selectedComponent)
        return;
    if(selectedComponent->gameObject->GetComponent<Engine::Transform>() == selectedComponent)
    {
        Engine::Transform* transform = selectedComponent->gameObject->GetComponent<Engine::Transform>();
        ImGui::DragFloat3("Position", &transform->position.x, 0.1f);
        ImGui::DragFloat3("Rotation", &transform->rotation.x, 0.1f);
        ImGui::DragFloat3("Scale", &transform->scale.x, 0.1f);
	}
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
        
        scene.DestroyGameObject(selectedEntity);
        selectedEntity = nullptr;
        currentEntityLabel = "  ";
    }
}





