#pragma once
#include "Scene/Scene.hpp"
#include "Entity/Component.hpp"

namespace Editor
{
	class Buttons
	{
	public:
		Buttons() {};
		~Buttons() {};

		void init();
		
		//Hub Buttons
		bool CreateProject();
		bool LoadProject();


		//Editor Buttons
		void selectEntity();
		void changeCmpntValue();
		void ShowEntity();
		void ManageEntity();
		bool startRuntime();


	private:

	};
}