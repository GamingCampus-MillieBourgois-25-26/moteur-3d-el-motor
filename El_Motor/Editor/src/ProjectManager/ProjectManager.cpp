#include "ProjectManager/ProjectManager.hpp"
#include "Entity/Component/MeshComponent.hpp"
#include <filesystem>
#include <fstream>
#include "External/Json/json.hpp"
#include <iostream>




Editor::ProjectManager& Editor::ProjectManager::Get()
{
    static ProjectManager instance;
    return instance;
}

Editor::ProjectManager::~ProjectManager() = default;






void Editor::ProjectManager::createProject(const std::string& name, std::shared_ptr<Engine::Scene>& scene) {

    std::filesystem::path path = "Projects/" + name;
    std::filesystem::create_directories(path);
    std::filesystem::create_directories(path / "Assets");
    std::filesystem::create_directories(path / "Scenes");

    // ProjectConfig.json
    nlohmann::json config;
    config["name"] = name;
    config["defaultScene"] = "MainScene.json";

    std::ofstream configFile(path / "ProjectConfig.json");
    configFile << config.dump(4);
    configFile.close();

    // MainScene.json
    nlohmann::json sceneJson;
    sceneJson["entities"] = nlohmann::json::array();

    std::ofstream sceneFile(path / "Scenes" / "MainScene.json");
    sceneFile << sceneJson.dump(4);
    sceneFile.close();

    currentProjectPath = path;

    scene = std::make_shared<Engine::Scene>();

    std::cout << "Project created: " << name << std::endl;

}


void Editor::ProjectManager::loadProject(const std::filesystem::path& path, std::shared_ptr<Engine::Scene>& scene) {
    currentProjectPath = path;

    std::ifstream configFile(path / "ProjectConfig.json");
    if (!configFile.is_open())
    {
        std::cout << "Invalid project" << std::endl;
        return;
    }

    nlohmann::json config;
    configFile >> config;
    std::cout << "Loaded project: " << config["name"] << std::endl;

    // Load the main scene only (single scene)
    std::filesystem::path mainScenePath = path / "Scenes" / "MainScene.json";
    loadScene(mainScenePath, scene);
}



void Editor::ProjectManager::loadScene(const std::filesystem::path& scenePath, std::shared_ptr<Engine::Scene>&  scene){


    std::ifstream sceneFile(scenePath);
    if (!sceneFile.is_open())
        return;

    nlohmann::json sceneJson;
    sceneFile >> sceneJson;

    // Create a new shared_ptr scene
    scene = std::make_shared<Engine::Scene>();

    for (auto& entityJson : sceneJson["entities"])
    {
        std::string name = entityJson["name"];
        Engine::GameObject* go = scene->CreateGameObject();
        go->SetName(name);

        for (auto& compJson : entityJson["components"])
        {
            std::string type = compJson["type"];

            if (type == "Transform")
            {
                Engine::Transform* t = go->GetTransform();

                auto pos = compJson["position"];
                t->position.x = pos[0];
                t->position.y = pos[1];
                t->position.z = pos[2];

                auto rot = compJson["rotation"];
                t->rotation.x = rot[0];
                t->rotation.y = rot[1];
                t->rotation.z = rot[2];

                auto scale = compJson["scale"];
                t->scale.x = scale[0];
                t->scale.y = scale[1];
                t->scale.z = scale[2];
            }
            else if (type == "MeshRenderer")
            {
                go->AddComponent<Engine::MeshComponent>();
            }
            else
            {
                std::cout << "Unknown component type: " << type << std::endl;
            }
        }
    }

}





void Editor::ProjectManager::saveProject(std::shared_ptr<Engine::Scene>& scene) {

    if (currentProjectPath.empty() || !scene)
        return;

    std::filesystem::path scenesFolder = currentProjectPath / "Scenes";
    std::filesystem::create_directories(scenesFolder);

    saveScene(*scene, scenesFolder / "MainScene.json");
}

void Editor::ProjectManager::saveScene(const Engine::Scene& scene, const std::filesystem::path& scenePath)
{
    nlohmann::json sceneJson;
    sceneJson["entities"] = nlohmann::json::array();

    for (auto* go : scene.GetRootObjects())
    {
        if (!go) continue;

        nlohmann::json entityJson;
        entityJson["name"] = go->GetName();

        entityJson["components"] = nlohmann::json::array();
        auto& components = go->GetAllComponents();
        for (auto* comp : components)
        {
            if (!comp) continue;

            nlohmann::json compJson;
            compJson["type"] = comp->GetTypeName();

            if (auto* t = dynamic_cast<Engine::Transform*>(comp))
            {
                compJson["position"] = { t->position.x, t->position.y, t->position.z };
                compJson["rotation"] = { t->rotation.x, t->rotation.y, t->rotation.z };
                compJson["scale"] = { t->scale.x, t->scale.y, t->scale.z };
            }

            entityJson["components"].push_back(compJson);
        }

        sceneJson["entities"].push_back(entityJson);
    }

    std::ofstream file(scenePath);
    file << sceneJson.dump(4);
}
