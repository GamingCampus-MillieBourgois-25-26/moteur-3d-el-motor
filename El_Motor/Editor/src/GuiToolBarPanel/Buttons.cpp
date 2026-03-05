#include "GuiToolBarPanel/Buttons.hpp"
#include "External/imgui/includes/CoreIncludes/imgui.h"
#include "External/imgui/includes/backend/imgui_impl_dx11.h"
#include "External/imgui/includes/backend/imgui_impl_glfw.h"
#include "External/ImGuiFileLog/includes/coreIncludes/ImGuiFileDialog.h"
#include "Assets/MeshAsset/MeshAsset.hpp"
#include "Entity/Component/MeshComponent.hpp"
#include "ScriptManager/ScriptManager.hpp"
#include "Logger/Logger.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Assets/Asset.hpp"
#include "Entity/GameObject.hpp"
#include "Entity/Component/RigidBodyComponent.hpp"

#include <iostream>



void Editor::Buttons::init() 
{

}

void Editor::Buttons::update(AssetManager& manager) {

}


bool Editor::Buttons::createProject()
{
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 buttonSize = ImVec2(250, 75);

    // ---------- TEXTE ----------
    const char* title = "El Motor";

    // Agrandir temporairement
    ImGui::SetWindowFontScale(2.5f);

    ImVec2 textSize = ImGui::CalcTextSize(title);

    ImGui::SetCursorPos(ImVec2(
        (windowSize.x - textSize.x) * 0.5f,
        (windowSize.y * 0.5f) - 300
    ));

    ImGui::Text("%s", title);

    // Remettre scale normal
    ImGui::SetWindowFontScale(1.0f);


    // ---------- BOUTON ----------
    ImGui::SetCursorPos(ImVec2(
        (windowSize.x - buttonSize.x) * 0.5f,
        ((windowSize.y - buttonSize.y) * 0.5f) - buttonSize.y
    ));

    if (ImGui::Button("Create Project", buttonSize))
    {
        if (GetSessionName() != "Null")
            return true;
        else
            SetSessionNameStatus("Incorrect project name , try again");
    }

    return false;

}

void Editor::Buttons::loadProject() {

    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 buttonSize = ImVec2(250, 75);
    ImVec2 LoadButtSize = ImVec2(800, 500);

    ImGui::SetCursorPos(ImVec2(
        (windowSize.x - buttonSize.x) * 0.5f,
        ((windowSize.y - buttonSize.y) * 0.5f) + buttonSize.y
    ));


    if (ImGui::Button("Load Project", buttonSize))
    {
        SetLoadSession(true);
    }

    if (GetLoadProject())
    {
        IGFD::FileDialogConfig config;
        config.path = "../../../../Game/Projects";

        // Ouvre le dialog pour sélectionner un dossier
        ImGuiFileDialog::Instance()->OpenDialog(
            "LoadProjectKey",          // key
            "Choose Project Folder",   // title
            nullptr,                   // filter null pour dossier
            config                 // dossier de départ
        );




        if (ImGuiFileDialog::Instance()->Display("LoadProjectKey", ImGuiWindowFlags_None, LoadButtSize))
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

    ImVec2 windowSize = ImGui::GetWindowSize();

    // ---------------- STATUS TEXT ----------------
    ImGui::SetWindowFontScale(1.5f);

    std::string status = GetSessionNameStatus();
    ImVec2 textSize = ImGui::CalcTextSize(status.c_str());
    ImGui::SetCursorPosX((windowSize.x - textSize.x) * 0.5f);
    ImGui::SetCursorPosY(((windowSize.y - textSize.y) * 0.5f) -180);
    ImGui::Text("%s", status.c_str());

    ImGui::SetWindowFontScale(1.0f);


    // ---------------- INPUT FIELD ----------------
    float inputWidth = 900.0f;

    ImGui::SetCursorPosX(((windowSize.x - inputWidth) * 0.5f));
    ImGui::SetCursorPosY(((windowSize.y - inputWidth) * 0.5f)+ 300);
    ImGui::SetNextItemWidth(inputWidth);

    if (ImGui::InputText("##ProjectName", bufferSessionName, sizeof(bufferSessionName),
        ImGuiInputTextFlags_EnterReturnsTrue))
    {
        if (CheckGoNameValid(bufferSessionName) || !CheckCaraterValid(bufferSessionName))
        {
            bufferSessionName[0] = '\0';
            SetSessionNameStatus("Incorrect project name , try again");
        }
        else
        {
            SetSessionName(bufferSessionName);
        }
    }

}

void Editor::Buttons::showScriptMenu(ScriptManager& scriptM)
{


    ImGui::Text("Scripts");
    ImGui::Separator();
    deleteScript(scriptM);
    AddScript(scriptM);
    ImGui::Separator();
    showScripts(scriptM);
}

void Editor::Buttons::deleteScript(ScriptManager& scriptM)
{
    if (ImGui::Button("Delete Script", ImVec2(90, 60)))
    {
        if (selectedScript.empty())
        {
            std::cout << "No script selected to delete\n";
            return;
        }


        std::filesystem::path rel(selectedScript);
        std::string scriptName;

        auto it = rel.begin();
        if (it != rel.end())
        {
            std::filesystem::path first = *it;

            if (first.has_extension())
                scriptName = first.stem().string();
            else
                scriptName = first.string();
        }
        else
        {
            scriptName = rel.stem().string();
        }

        scriptM.DeleteScript(GetProjectPath(),selectedScript);


        selectedScript.clear();

        std::cout << "Requested deletion of script: " << scriptName << std::endl;
    }

    ImGui::SameLine();
    if (ImGui::Button("Add", ImVec2(90, 60)))
    {
        if (GetScriptName() != "Null") {
            scriptM.createScript(GetScriptName(), GetSessionName());
        }

    }
}

void Editor::Buttons::editScript(ScriptManager& scriptM)
{

}

void Editor::Buttons::AddScript(ScriptManager& scriptM)
{

    static char bufferScriptName[256] = "";

        

    if (ImGui::InputText("Script Name", bufferScriptName, sizeof(bufferScriptName), ImGuiInputTextFlags_EnterReturnsTrue))
    {
        if (!CheckScriptNameValid(bufferScriptName) || !CheckCaraterValid(bufferScriptName) )
        {
            SetScriptName(bufferScriptName);
        }
        else
        {
            strncpy(bufferScriptName, "Script name", sizeof(bufferScriptName));
            bufferScriptName[sizeof(bufferScriptName) - 1] = '\0';
        }
    }


}

void Editor::Buttons::showScripts(ScriptManager& scriptM)
{
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImGui::BeginChild("ScriptList", ImVec2(0, 0), true);

    std::vector<std::string> scriptFiles;

    
    std::string basePath = "../../../../Game/Projects/" + GetSessionName() + "/Scripts";

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
bool Editor::Buttons::CheckScriptNameValid(const std::string& str)
{

    return !str.empty()
        && !std::all_of(str.begin(), str.end(),
            [](unsigned char c) { return std::isspace(c); })
        && (str.ends_with(".cpp") || str.ends_with(".hpp"));
}

bool Editor::Buttons::reloadScript()
{
    if (ImGui::Button("Reaload", ImVec2(150, 50)))
    {
        return true;
    }
    return false;
}

bool Editor::Buttons::startRuntime()
{
    if (ImGui::Button("Run", ImVec2(150, 50)))
    {
        return true;
    }
    return false;

}

void Editor::Buttons::loadAssets(AssetManager& manager)
{


    if (ImGui::Button("Load Assets", ImVec2(150, 50)))
    {
        SetLoadAsset(true);
    }
 


    if (GetLoadAsset() == true) {

        IGFD::FileDialogConfig config;
        config.path = "Assets";
        ImGuiFileDialog::Instance()->OpenDialog(
            "LoadAssetKey",
            "Choose Asset",
            ".png,.jpg,.obj,.fbx,.mp3",
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
                    Engine::LoggerManager::Get().LogInfo("Asset Loaded succesfuly : " + filePath);
                }
                else if (extension == ".mp3")
                {
                    
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

 
	ImGui::BeginChild("ComponentList", ImVec2(0,0), true);//Component list child
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

	const char* items[] = { "MeshRenderer", "Camera", "RigidBody" };//List of component types to add
    const int itemCount = IM_ARRAYSIZE(items);

    ImGui::SetNextWindowSize(ImVec2(200, 300));
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

	if (ImGui::Button("Add Component" , ImVec2(0,0))) //Button to add the selected component type to the selected entity
    {
        switch (currentItem)
        {
        case 0: selectedEntity->AddComponent<Engine::MeshComponent>();
            break;

        case 1: /* Add Camera */ break;

        case 2: selectedEntity->AddComponent<Engine::RigidBodyComponent>();
            break;
        }
    }
    delComponent();
}

void Editor::Buttons::delComponent()
{
    ImGui::SameLine();
    if (selectedEntity->GetComponent<Engine::Transform>() != selectedComponent && selectedComponent && ImGui::Button("Delete Component"))
    {
		
	}
}

void Editor::Buttons::editComponent(const AssetManager& assetM)
{
    if (!selectedComponent)
        return;

    if (auto* transform = dynamic_cast<Engine::Transform*>(selectedComponent))
    {
        ImGui::DragFloat3("Position", &transform->position.m_x, 0.1f);
        ImGui::DragFloat3("Rotation", &transform->rotation.m_x, 0.1f);
        ImGui::DragFloat3("Scale", &transform->scale.m_x, 0.1f);
    }

    if (auto* meshComp = dynamic_cast<Engine::MeshComponent*>(selectedComponent))
    {
        ImGui::Text("Mesh");

        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
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


void Editor::Buttons::playSound(Engine::MiniAudioSystem sound)
{
    if (ImGui::Button("Play Sound", ImVec2(150, 50)))
    {
        return;
    }
}

void Editor::Buttons::stopPlayingSound(Engine::MiniAudioSystem sound)
{
    if (ImGui::Button("Stop Sound", ImVec2(150, 50)))
    {
       return;
    }
}

bool Editor::Buttons::saveProject()
{
    if (ImGui::Button("Save", ImVec2(150, 50)))
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
        if (CheckGoNameValid(buffer) || !CheckCaraterValid(buffer))//true if there is only spaces in the buffer
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