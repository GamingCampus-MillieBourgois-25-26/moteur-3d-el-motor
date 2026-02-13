#include "Scene/Scene.hpp"
#include "Logger/Logger.hpp"
#include "Entity/Entity.hpp"
#include <algorithm>

Scene::~Scene() {
    for (GameObject* go : rootObjects) {
        delete go;
    }
    rootObjects.clear();
}

// Create
GameObject* Scene::CreateGameObject() {
    GameObject* go = new GameObject();
    rootObjects.push_back(go);
    Engine::LoggerManager::Get().LogInfo("Scene: GameObject added");
    return go;
}

// Destroy
void Scene::DestroyGameObject(GameObject* go) {
    Engine::LoggerManager::Get().LogInfo("GameObject destroyed");

    if (!go) return;

    // Remove from root list if present
    rootObjects.erase(
        std::remove(rootObjects.begin(), rootObjects.end(), go),
        rootObjects.end()
    );

    delete go;
}

// Update
void Scene::Update(float dt) {
    for (GameObject* go : rootObjects) {
        go->Update(dt);
    }
}

// Getter
const std::vector<GameObject*>& Scene::GetRootObjects() const {
    return rootObjects;
}