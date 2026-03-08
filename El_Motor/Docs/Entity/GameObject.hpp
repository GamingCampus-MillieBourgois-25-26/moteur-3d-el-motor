#pragma once

#include <vector>
#include <type_traits>
#include <utility>
#include <algorithm>
#include <string>

#include "Entity/Component.hpp"
#include "Entity/Transform.hpp"

namespace Engine {

    /// <summary>
    /// Represents an object in the scene.
    /// A GameObject can contain multiple components and be part of a hierarchy.
    /// </summary>
    class GameObject {
    private:

        /// <summary>
        /// Name of the GameObject (useful for debugging or editor).
        /// </summary>
        std::string name;

        /// <summary>
        /// List of components attached to this GameObject.
        /// </summary>
        std::vector<Component*> components;

        /// <summary>
        /// Parent GameObject in the hierarchy.
        /// </summary>
        GameObject* parent = nullptr;

        /// <summary>
        /// Children GameObjects in the hierarchy.
        /// </summary>
        std::vector<GameObject*> children;

    public:

        /// <summary>
        /// Creates a GameObject with an optional name.
        /// </summary>
        /// <param name="name">Name of the GameObject</param>
        GameObject(const std::string& name = "GameObject");

        /// <summary>
        /// Destructor responsible for cleaning up components.
        /// </summary>
        ~GameObject();

        // =========================
        // Update
        // =========================

        /// <summary>
        /// Updates all components attached to this GameObject.
        /// </summary>
        /// <param name="dt">Delta time between frames</param>
        void Update(float dt);

        // =========================
        // Name
        // =========================

        /// <summary>
        /// Returns the GameObject name.
        /// </summary>
        const std::string& GetName() const;

        /// <summary>
        /// Sets a new name for the GameObject.
        /// </summary>
        /// <param name="newName">New object name</param>
        void SetName(const std::string& newName);

        // =========================
        // Hierarchy
        // =========================

        /// <summary>
        /// Sets the parent GameObject.
        /// Updates the hierarchy structure.
        /// </summary>
        /// <param name="newParent">Parent GameObject</param>
        void SetParent(GameObject* newParent);

        /// <summary>
        /// Returns the parent GameObject.
        /// </summary>
        GameObject* GetParent() const;

        /// <summary>
        /// Returns the children GameObjects.
        /// </summary>
        const std::vector<GameObject*>& GetChildren() const;

        // =========================
        // Components
        // =========================

        /// <summary>
        /// Adds a new component of type T to this GameObject.
        /// </summary>
        /// <typeparam name="T">Component type</typeparam>
        /// <typeparam name="Args">Constructor arguments</typeparam>
        /// <returns>Pointer to the created component</returns>
        template<typename T, typename... Args>
        T* AddComponent(Args&&... args) {
            static_assert(std::is_base_of<Component, T>::value,
                "T must inherit from Component");

            T* comp = new T(std::forward<Args>(args)...);
            comp->gameObject = this;

            components.push_back(comp);
            return comp;
        }

        /// <summary>
        /// Returns the first component of type T attached to this GameObject.
        /// </summary>
        /// <typeparam name="T">Component type</typeparam>
        /// <returns>Pointer to the component if found</returns>
        template<typename T>
        T* GetComponent() {
            for (Component* c : components) {
                if (auto* casted = dynamic_cast<T*>(c))
                    return casted;
            }
            return nullptr;
        }

        /// <summary>
        /// Checks whether the GameObject contains a component of type T.
        /// </summary>
        /// <typeparam name="T">Component type</typeparam>
        /// <returns>True if the component exists</returns>
        template<typename T>
        bool HasComponent() const {
            for (Component* c : components) {
                if (dynamic_cast<T*>(c))
                    return true;
            }
            return false;
        }

        /// <summary>
        /// Removes a component of type T from this GameObject.
        /// </summary>
        /// <typeparam name="T">Component type</typeparam>
        /// <returns>True if the component was removed</returns>
        template<typename T>
        bool RemoveComponent() {
            static_assert(std::is_base_of<Component, T>::value,
                "T must inherit from Component");

            // Prevent removing the Transform component
            if constexpr (std::is_same<T, Transform>::value) {
                return false;
            }

            for (auto it = components.begin(); it != components.end(); ++it) {
                if (auto* casted = dynamic_cast<T*>(*it)) {

                    casted->OnDestroy();
                    delete casted;

                    components.erase(it);
                    return true;
                }
            }

            return false;
        }

        /// <summary>
        /// Returns all components attached to the GameObject.
        /// </summary>
        const std::vector<Component*>& GetAllComponents() const;

        // =========================
        // Transform Shortcut
        // =========================

        /// <summary>
        /// Returns the Transform component of the GameObject.
        /// Every GameObject should have one.
        /// </summary>
        /// <returns>Pointer to the Transform component</returns>
        Transform* GetTransform();
    };

}