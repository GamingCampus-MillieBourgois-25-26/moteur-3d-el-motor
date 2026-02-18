#pragma once

#include <vector>
#include <type_traits>
#include <utility>
#include <algorithm>
#include <string>

#include "Entity/Component.hpp"
#include "Entity/Transform.hpp"

namespace Engine {
    class GameObject {
    private:
        std::string name;

        std::vector<Component*> components;

        GameObject* parent = nullptr;
        std::vector<GameObject*> children;

    public:
        GameObject(const std::string& name = "GameObject");
        ~GameObject();

        // Update
        void Update(float dt);

        // Name
        const std::string& GetName() const;
        void SetName(const std::string& newName);

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
}