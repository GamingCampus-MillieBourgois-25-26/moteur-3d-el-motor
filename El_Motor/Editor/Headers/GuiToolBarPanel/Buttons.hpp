#pragma once
#include "Scene/Scene.hpp"

namespace Editor
{
	class Buttons
	{
	private:
		
	protected:
		int selectedEntity = 0;
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
		bool showEntity();
		void createEntity(Engine::Scene& scene);
		void delEntity(Engine::Scene& scene);
		bool startRuntime();


	

	};
}