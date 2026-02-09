#include "../../Headers/Entity/GameObject.hpp"

// Constructor / Destructor
GameObject::GameObject() {
    AddComponent<Transform>();
}
GameObject::~GameObject() {
    // destroy components
    for (Component* c : components) {
        if (c) {
            c->OnDestroy();
            delete c;
        }
    }
    components.clear();

    // detach from parent
    if (parent) {
        auto& siblings = parent->children;
        siblings.erase(
            std::remove(siblings.begin(), siblings.end(), this),
            siblings.end()
        );
    }

    // destroy children
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
    // remove from old parent
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
