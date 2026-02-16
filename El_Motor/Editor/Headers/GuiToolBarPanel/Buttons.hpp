#pragma once
#include "Scene/Scene.hpp"
#include "Entity/GameObject.hpp"
namespace Editor
{
	class Buttons
	{
	private:
		
	protected:
		Engine::GameObject* selectedEntity = nullptr;
		int CurrentEntity;
	public:
		Buttons() {};
		~Buttons() {};

		void init();
		
		//Hub Buttons
		bool createProject();
		bool loadProject();


		//Editor Buttons
		void selectEntity(Engine::Scene& scene);
		bool changeCmpntValue();
		void createEntity(Engine::Scene& scene);
		void delEntity(Engine::Scene& scene);
		bool startRuntime();

	

	};
}