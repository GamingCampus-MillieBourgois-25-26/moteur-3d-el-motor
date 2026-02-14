#pragma once

#include <iostream>
#include "Application/App.hpp"
#include "ImGuiLayer/ImGuiLayer.hpp"

namespace Editor {
	class HubManager
	{
	protected:
		Engine::Application app;



	public:

		HubManager();
		~HubManager();


		//Functions
		void Init();
		void CreateProject();
		void LoadProject();



		//Getters
		std::string GetSessionName() const { return sessionName; }



		//Setters
		void SetSessionName(std::string name) { sessionName = name; }

	private:


		//Variables
		ImGuiLayer guiLayer;
		std::string sessionName = "Null";

	};
}