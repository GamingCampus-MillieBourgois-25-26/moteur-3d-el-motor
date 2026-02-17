#pragma once
#include "Scene/Scene.hpp"
#include "Entity/GameObject.hpp"
#include <string>
namespace Editor
{
	class Buttons
	{
	private:
		
	protected:
		Engine::GameObject* selectedEntity = nullptr;
		std::string currentEntityLabel;

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

	

	};
}