#pragma once

#include <vector>
#include <type_traits>
#include <utility>
#include <algorithm>
#include <string>

#include "Entity/Component.hpp"
#include "Entity/Transform.hpp"

namespace Engine {

    /**
     * @brief Represents an object in the scene.
     *
     * A GameObject can contain multiple components and be part of a hierarchy
     * with parent and child GameObjects. Components define the behavior or
     * data of the GameObject.
     */
    class GameObject {
    private:

        /// @brief Name of the GameObject (useful for debugging or editor)
        std::string name;

        /// @brief List of components attached to this GameObject
        std::vector<Component*> components;

        /// @brief Parent GameObject in the hierarchy
        GameObject* parent = nullptr;

        /// @brief Children GameObjects in the hierarchy
        std::vector<GameObject*> children;

    public:

        /**
         * @brief Creates a GameObject with an optional name.
         * @param name Name of the GameObject
         */
        GameObject(const std::string& name = "GameObject");

        /**
         * @brief Destructor responsible for cleaning up components.
         */
        ~GameObject();

        // =========================
        // Update
        // =========================

        /**
         * @brief Updates all components attached to this GameObject.
         * @param dt Delta time between frames
         */
        void Update(float dt);

        // =========================
        // Name
        // =========================

        /**
         * @brief Returns the GameObject name.
         * @return Name of the GameObject
         */
        const std::string& GetName() const;

        /**
         * @brief Sets a new name for the GameObject.
         * @param newName New object name
         */
        void SetName(const std::string& newName);

        // =========================
        // Hierarchy
        // =========================

        /**
         * @brief Sets the parent GameObject.
         * Updates the hierarchy structure automatically.
         * @param newParent Parent GameObject
         */
        void SetParent(GameObject* newParent);

        /**
         * @brief Returns the parent GameObject.
         * @return Pointer to the parent GameObject
         */
        GameObject* GetParent() const;

        /**
         * @brief Returns the children GameObjects.
         * @return Vector of pointers to child GameObjects
         */
        const std::vector<GameObject*>& GetChildren() const;

        // =========================
        // Components
        // =========================

        /**
         * @brief Adds a new component of type T to this GameObject.
         * @tparam T Component type (must inherit from Component)
         * @tparam Args Constructor argument types
         * @param args Arguments forwarded to the component constructor
         * @return Pointer to the newly created component
         */
        template<typename T, typename... Args>
        T* AddComponent(Args&&... args) {
            static_assert(std::is_base_of<Component, T>::value,
                "T must inherit from Component");

            T* comp = new T(std::forward<Args>(args)...);
            comp->gameObject = this;

            components.push_back(comp);
            return comp;
        }

        /**
         * @brief Returns the first component of type T attached to this GameObject.
         * @tparam T Component type
         * @return Pointer to the component if found, nullptr otherwise
         */
        template<typename T>
        T* GetComponent() {
            for (Component* c : components) {
                if (auto* casted = dynamic_cast<T*>(c))
                    return casted;
            }
            return nullptr;
        }

        /**
         * @brief Checks whether the GameObject contains a component of type T.
         * @tparam T Component type
         * @return True if a component of type T exists
         */
        template<typename T>
        bool HasComponent() const {
            for (Component* c : components) {
                if (dynamic_cast<T*>(c))
                    return true;
            }
            return false;
        }

        /**
         * @brief Removes a component of type T from this GameObject.
         * @tparam T Component type
         * @return True if the component was successfully removed
         */
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

        /**
         * @brief Returns all components attached to the GameObject.
         * @return Vector of pointers to all components
         */
        const std::vector<Component*>& GetAllComponents() const;

        // =========================
        // Transform Shortcut
        // =========================

        /**
         * @brief Returns the Transform component of the GameObject.
         * Every GameObject should have a Transform component.
         * @return Pointer to the Transform component
         */
        Transform* GetTransform();
    };

} // namespace Engine