#include "Entity/GameObject.hpp"
#include "Logger/Logger.hpp"

// Constructor
GameObject::GameObject() {
    AddComponent<Transform>();
    Engine::LoggerManager::Get().LogInfo("GameObject created");
}

// Destructor
GameObject::~GameObject() {
    Engine::LoggerManager::Get().LogInfo("GameObject destroyed");

    // Destroy components
    for (Component* c : components) {
        if (c) {
            c->OnDestroy();
            delete c;
        }
    }
    components.clear();

    // Detach from parent
    if (parent) {
        auto& siblings = parent->children;
        siblings.erase(
            std::remove(siblings.begin(), siblings.end(), this),
            siblings.end()
        );
    }

    // Destroy children
    for (GameObject* child : children) {
        delete child;
    }
    children.clear();
}

// Update
void GameObject::Update(float dt) {
    for (Component* c : components)
        c->Update(dt);

    for (GameObject* child : children)
        child->Update(dt);
}

// Hierarchy
void GameObject::SetParent(GameObject* newParent) {
    if (newParent == this)
        return;

    // Remove from old parent
    if (parent) {
        auto& siblings = parent->children;
        siblings.erase(
            std::remove(siblings.begin(), siblings.end(), this),
            siblings.end()
        );
    }

    parent = newParent;

    if (parent)
        parent->children.push_back(this);
}

GameObject* GameObject::GetParent() const {
    return parent;
}

const std::vector<GameObject*>& GameObject::GetChildren() const {
    return children;
}

// Components
const std::vector<Component*>& GameObject::GetAllComponents() const {
    return components;
}

// Shortcut Transform
Transform* GameObject::GetTransform() {
    return GetComponent<Transform>();
}