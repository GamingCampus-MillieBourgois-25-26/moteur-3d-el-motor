#pragma once

//#include "AssetManager/AssetManager.hpp"
#include "Entity/GameObject.hpp"

#include <vector>

namespace Engine {
	class Scene {
	private:
		std::vector<GameObject*> rootObjects;

	public:
		Scene() = default;
		~Scene();

		GameObject* CreateGameObject();
		void DestroyGameObject(GameObject* go);

		void Update(float dt);

		const std::vector<GameObject*>& GetRootObjects() const;
	};
}