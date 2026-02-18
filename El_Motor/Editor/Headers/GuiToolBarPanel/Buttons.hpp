#pragma once
#include "Scene/Scene.hpp"
#include "Entity/GameObject.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Assets/Asset.hpp"
#include <string>
#include <filesystem>
namespace Editor
{
	class Buttons
	{
	private:
		
	protected:
		//Selected Entity pointeur + label
		Engine::GameObject* selectedEntity = nullptr;
		std::string currentEntityLabel;

		//Selected Component pointer
		Engine::Component* selectedComponent = nullptr;
		
	public:
		Buttons() {};
		~Buttons() {};

		void init();
		
		//Hub Buttons
		bool createProject();
		bool loadProject();


		//Editor Entity Buttons
		void selectEntity(Engine::Scene& scene);
		void createEntity(Engine::Scene& scene);
		void delEntity(Engine::Scene& scene);

		//Editor Component Buttons
		void showCmpnt(Engine::Scene& scene);
		void addComponent();
		void delComponent();
		void editComponent();




		bool startRuntime();


		void loadAssets(AssetManager& manager);

	};
}