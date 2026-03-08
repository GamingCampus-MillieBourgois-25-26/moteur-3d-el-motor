#pragma once

//#include "AssetManager/AssetManager.hpp"
#include "Entity/GameObject.hpp"

#include <vector>

namespace Engine {

    /**
     * @brief Represents a scene containing multiple GameObjects.
     *
     * The Scene manages creation, destruction, and updating of root GameObjects.
     * Child GameObjects are updated recursively through their parent hierarchy.
     */
    class Scene {
    private:
        /**
         * @brief Root GameObjects in the scene (those without a parent).
         */
        std::vector<GameObject*> rootObjects;

    public:
        /**
         * @brief Default constructor.
         */
        Scene() = default;

        /**
         * @brief Destructor.
         *
         * Cleans up all GameObjects in the scene.
         */
        ~Scene();

        /**
         * @brief Creates a new GameObject and adds it to the scene as a root object.
         *
         * @return Pointer to the newly created GameObject.
         */
        GameObject* CreateGameObject();

        /**
         * @brief Destroys a GameObject and removes it from the scene.
         *
         * Also removes it from the rootObjects list if necessary.
         *
         * @param go Pointer to the GameObject to destroy.
         */
        void DestroyGameObject(GameObject* go);

        /**
         * @brief Updates all root GameObjects and their children recursively.
         *
         * Calls Update(dt) on each component of every GameObject.
         *
         * @param dt Delta time in seconds since the last frame.
         */
        void Update(float dt);

        /**
         * @brief Returns the root GameObjects of the scene.
         *
         * Root objects are those with no parent. Child GameObjects can be accessed through their parents.
         *
         * @return Const reference to the vector of root GameObjects.
         */
        const std::vector<GameObject*>& GetRootObjects() const;
    };

} // namespace Engine