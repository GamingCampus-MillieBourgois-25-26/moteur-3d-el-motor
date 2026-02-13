#pragma once

#include <vector>
#include <type_traits>
#include <utility>
#include <algorithm>

#include "Component.hpp"
#include "Transform.hpp"

class GameObject {
private:
    std::vector<Component*> components;

    GameObject* parent = nullptr;
    std::vector<GameObject*> children;

public:
    GameObject();
    ~GameObject();

    // Update
    void Update(float dt);

    // Hierarchy
    void SetParent(GameObject* newParent);
    GameObject* GetParent() const;
    const std::vector<GameObject*>& GetChildren() const;

    // Components
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value,
            "T must inherit from Component");

        T* comp = new T(std::forward<Args>(args)...);
        comp->gameObject = this;

        components.push_back(comp);
        return comp;
    }

    template<typename T>
    T* GetComponent() {
        for (Component* c : components) {
            if (auto* casted = dynamic_cast<T*>(c))
                return casted;
        }
        return nullptr;
    }

    const std::vector<Component*>& GetAllComponents() const;

    // Shortcut Transform
    Transform* GetTransform();
};