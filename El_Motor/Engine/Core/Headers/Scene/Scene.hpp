#pragma once

//#include "AssetManager/AssetManager.hpp"
#include "Entity/GameObject.hpp"

#include <vector>

namespace Engine {

    /// <summary>
    /// Represents a scene containing multiple GameObjects.
    /// Manages creation, destruction, and updating of root GameObjects.
    /// </summary>
    class Scene {
    private:
        /// <summary>
        /// Root GameObjects in the scene (no parent)
        /// </summary>
        std::vector<GameObject*> rootObjects;

    public:
        Scene() = default;
        ~Scene();

        /// <summary>
        /// Creates a new GameObject and adds it to the rootObjects list.
        /// </summary>
        /// <returns>Pointer to the newly created GameObject</returns>
        GameObject* CreateGameObject();

        /// <summary>
        /// Destroys a GameObject and removes it from the scene.
        /// </summary>
        /// <param name="go">Pointer to the GameObject to destroy</param>
        void DestroyGameObject(GameObject* go);

        /// <summary>
        /// Updates all root GameObjects and their children recursively.
        /// </summary>
        /// <param name="dt">Delta time in seconds</param>
        void Update(float dt);

        /// <summary>
        /// Returns a reference to the root GameObjects of the scene.
        /// </summary>
        /// <returns>Const reference to the vector of root GameObjects</returns>
        const std::vector<GameObject*>& GetRootObjects() const;
    };
}