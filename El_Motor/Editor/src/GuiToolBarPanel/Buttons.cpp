#include "GuiToolBarPanel/Buttons.hpp"
#include "External/imgui/includes/CoreIncludes/imgui.h"
#include "External/imgui/includes/backend/imgui_impl_dx11.h"
#include "External/imgui/includes/backend/imgui_impl_glfw.h"
#include "External/ImGuiFileLog/includes/coreIncludes/ImGuiFileDialog.h"
#include "Assets/MeshAsset/MeshAsset.hpp"
#include "Entity/Component/MeshComponent.hpp"
#include "ScriptManager/ScriptManager.hpp"
#include "Logger/Logger.hpp"
#include <iostream>



void Editor::Buttons::init() 
{

}

void Editor::Buttons::update(AssetManager& manager) {

}


bool Editor::Buttons::createProject()
{

    if (ImGui::Button("Create Project", ImVec2(200, 50)))
    {
        if(GetSessionName() != "Null")
        return true;

        else
        SetSessionNameStatus("Incorrect project name , try again");
    }
    return false;

}

void Editor::Buttons::loadProject() {

    if (ImGui::Button("Load Project", ImVec2(200, 50)))
    {
        SetLoadSession(true);
    }

    if (GetLoadProject())
    {
        IGFD::FileDialogConfig config;
        config.path = "Projects";

        // Ouvre le dialog pour sélectionner un dossier
        ImGuiFileDialog::Instance()->OpenDialog(
            "LoadProjectKey",          // key
            "Choose Project Folder",   // title
            nullptr,                   // filter null pour dossier
            config                 // dossier de départ
        );

        if (ImGuiFileDialog::Instance()->Display("LoadProjectKey", ImGuiWindowFlags_None, ImVec2(200, 50)))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string folderPath = ImGuiFileDialog::Instance()->GetCurrentPath();
                std::cout << "Selected project folder: " << folderPath << std::endl;

                // Appelle ton ProjectManager avec ce dossier
                SetProjectPath(folderPath);
                SetLoadProjReady(true);
            }

            ImGuiFileDialog::Instance()->Close();
            SetLoadSession(false); // reset toggle
        }

    }
}

void Editor::Buttons::projectName()
{
    static char bufferSessionName[256] = "";
    ImGui::Text(GetSessionNameStatus().c_str());
    if (ImGui::InputText("Project Name", bufferSessionName, sizeof(bufferSessionName), ImGuiInputTextFlags_EnterReturnsTrue))
    {
        if (CheckGoNameValid(bufferSessionName) || !CheckCaraterValid(bufferSessionName))
        {
            strncpy(bufferSessionName,"", sizeof(bufferSessionName));
            bufferSessionName[sizeof(bufferSessionName) - 1] = '\0';
            SetSessionNameStatus("Incorrect project name , try again");
        }
        else {
            SetSessionName(bufferSessionName);
        }
    }
}

void Editor::Buttons::showScriptMenu(ScriptManager& scriptM)
{
	ImGui::BeginChild("ScriptMenu", ImVec2(250, 0), true);
    ImGui::Text("Scripts");
    ImGui::Separator();
    AddScript(scriptM,"Test");
    ImGui::Separator();
    showScripts(scriptM);
    ImGui::EndChild();
}

void Editor::Buttons::deleteScript(ScriptManager& scriptM) const
{

}

void Editor::Buttons::editScript(ScriptManager& scriptM)
{
}

void Editor::Buttons::AddScript(ScriptManager& scriptM , std::string name)
{
    if (ImGui::Button("Add Script", ImVec2(80, 25))) {
        scriptM.createScript(name, GetSessionName());
    }
}

void Editor::Buttons::showScripts(ScriptManager& scriptM)
{
    ImGui::BeginChild("ScriptList", ImVec2(250, 0), true);

    std::vector<std::string> scriptFiles;

    
    std::string basePath = "Projects/" + GetSessionName() + "/Scripts";

    // Vérifie que le dossier existe
    if (!std::filesystem::exists(basePath))
    {
        ImGui::Text("Le dossier Scripts n'existe pas !");
        ImGui::EndChild();
        return;
    }

    
    for (const auto& entry : std::filesystem::recursive_directory_iterator(basePath))
    {
        if (entry.is_regular_file())
        {
            std::string path = entry.path().string();

            
            if (path.size() >= 4 && (path.substr(path.size() - 4) == ".cpp" || path.substr(path.size() - 4) == ".hpp"))
            {
                
                scriptFiles.push_back(std::filesystem::relative(entry.path(), basePath).string());
            }
        }
    }

    
    for (size_t i = 0; i < scriptFiles.size(); ++i)
    {
        const std::string& name = scriptFiles[i];
        ImGui::PushID(static_cast<int>(i));

        bool isSelected = (selectedScript == name);
        if (ImGui::Selectable(name.c_str(), isSelected))
        {
            selectedScript = name;
        }

        ImGui::PopID();
    }

    ImGui::EndChild();
}
bool Editor::Buttons::CheckScriptNameValid(const std::string& str, bool IsCpp)
{
    if (IsCpp)
    {
        if (str.empty() || str.ends_with(".cpp") || all_of(str.begin(), str.end(),
            [](unsigned char c) {
                return std::isspace(c);
            })) 
        {}

    }
    else if (!IsCpp)
    {
        if (str.empty() || str.ends_with(".hpp") || all_of(str.begin(), str.end(),
            [](unsigned char c) {
                return std::isspace(c);
            })) 
        {}
    }

    else
    {
        SetSessionNameStatus("Type a script name, then press Enter to confirm");
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


    if (ImGui::Button("Load Assets", ImVec2(80, 25)))
    {
        SetLoadAsset(true);
    }
 


    if (GetLoadAsset() == true) {

        IGFD::FileDialogConfig config;
        config.path = "Assets";
        ImGuiFileDialog::Instance()->OpenDialog(
            "LoadAssetKey",
            "Choose Asset",
            ".png,.jpg,.obj,.fbx",
            config
        );

        if (ImGuiFileDialog::Instance()->Display("LoadAssetKey", ImGuiWindowFlags_None, ImVec2(1500, 500)))
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
            
            SetLoadAsset(false);
            ImGuiFileDialog::Instance()->Close();
        }
    }
}

void Editor::Buttons::test()
{
    //auto& currentSelected = selectedEntity->GetAllComponents();
    //for (int i = 0; selectedEntity->GetAllComponents().size(); i++) {
    //    if (currentSelected[i] == AssetManager:: ) {

    //    }
    //}
}

void Editor::Buttons::selectGO(std::shared_ptr<Engine::Scene>& scene)
{
    ImGui::BeginChild("Hierarchy", ImVec2(250, 0), true);
    auto& currentSelected = scene->GetRootObjects();

    for (int i = 0; i < scene->GetRootObjects().size() ; i++)
    {
       
        Engine::GameObject* go = currentSelected[i];
        if (!go) continue; // skip nullptr



        ImGui::PushID(i);
        std::string label = go->GetName();//Name des entité
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

void Editor::Buttons::showCmpnt(const AssetManager& assetM)
{
    if (!selectedEntity)
        return;

    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

  

	ImGui::BeginChild("ComponentList", ImVec2(0, 0), true);//Component list child
	addComponent();//Button to add component to the selected entity
    ChangeGOName();
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
		//Show the component's editable properties if it's selected
    }
    editComponent(assetM);
    ImGui::EndChild();
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
        case 0: selectedEntity->AddComponent<Engine::MeshComponent>();
            break;
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
		
		
	}
}

void Editor::Buttons::editComponent(const AssetManager& assetM)
{
    if (!selectedComponent)
        return;

    if (auto* transform = dynamic_cast<Engine::Transform*>(selectedComponent))
    {
        ImGui::DragFloat3("Position", &transform->position.x, 0.1f);
        ImGui::DragFloat3("Rotation", &transform->rotation.x, 0.1f);
        ImGui::DragFloat3("Scale", &transform->scale.x, 0.1f);
    }

    if (auto* meshComp = dynamic_cast<Engine::MeshComponent*>(selectedComponent))
    {
        ImGui::Text("Mesh");

        if (ImGui::BeginCombo("##MeshSelect",
            meshComp->GetMesh() ? meshComp->GetMesh()->path.c_str() : "None"))
        {
            for (const auto& [path, asset] : assetM.GetMeshes())
            {
                auto mesh = std::dynamic_pointer_cast<MeshAsset>(asset);
                if (!mesh)
                    continue;

                bool isSelected = (meshComp->GetMesh() == mesh);

                if (ImGui::Selectable(path.c_str(), isSelected))
                {
                    meshComp->SetMesh(mesh);
                }

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }
    }
}

bool Editor::Buttons::saveProject()
{
    if (ImGui::Button("Save", ImVec2(200, 50)))
    {
            return true;
    }
    return false;
}


void Editor::Buttons::createGO(std::shared_ptr<Engine::Scene>& scene)
{
    if (ImGui::Button("Create GameObject", ImVec2(150, 50)))
    {
       scene->CreateGameObject();
    }
}

void Editor::Buttons::delGO(std::shared_ptr<Engine::Scene>& scene)
{
    if (ImGui::Button("Delete GameObject", ImVec2(150, 50)))
    {
        
        scene->DestroyGameObject(selectedEntity);
        selectedEntity = nullptr;
        currentEntityLabel = "  ";
    }
}

void Editor::Buttons::ChangeGOName()
{
    if (!selectedEntity)
        return;
static char buffer[256] = "";
    
    Engine::GameObject* previousGO = nullptr;
    

    if (selectedEntity != previousGO)
    {
        strncpy(buffer, selectedEntity->GetName().c_str(), sizeof(buffer));
        buffer[sizeof(buffer) - 1] = '\0';
        previousGO = selectedEntity;
    }


    if (ImGui::InputText("Name", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue))//active only after user press enter
    {
        if (!CheckGoNameValid(buffer) || !CheckCaraterValid(buffer))//true if there is only spaces in the buffer
        {
            selectedEntity->SetName("GameObject");
        }
        else
        {
            selectedEntity->SetName(buffer);
        }
    }
}

bool Editor::Buttons::CheckGoNameValid(const std::string& str)
{
    return std::all_of(str.begin(), str.end(),
        [](unsigned char c)
        {
            return std::isspace(c);
        });
}

bool Editor::Buttons::CheckCaraterValid(const std::string& str)
{
        return std::ranges::all_of(str, [](unsigned char c)
            {
                return std::isalnum(c) || c == '_' || c == '-';
            });
}





