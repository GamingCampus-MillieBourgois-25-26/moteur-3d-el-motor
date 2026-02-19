#pragma once
#include "Scene/Scene.hpp"
#include "Entity/GameObject.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Assets/Asset.hpp"
#include <string>
#include <filesystem>
namespace Editor
{
	// GO = GameObject
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
		void selectGO(Engine::Scene& scene);//select GO
		void createGO(Engine::Scene& scene);//create GO
		void delGO(Engine::Scene& scene);// delete GO
		void ChangeGOName();//Change the name of the GO selected
		bool CheckGoNameValid(const std::string& str);//Check if the GO name isn't only composed of spaces

		//Editor Component Buttons
		void showCmpnt(Engine::Scene& scene);//show all the component of a selected GO
		void addComponent(); //add a component to a selecte GO
		void delComponent(); //delete a component of a selected GO
		void editComponent(); //Change the value of the selected Go Transform




		bool startRuntime();


		void loadAssets(AssetManager& manager);

	};
}