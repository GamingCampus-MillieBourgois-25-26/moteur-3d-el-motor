#pragma once
#include <iostream>

namespace Editor
{
	class HubManager
	{
	protected:
		//Engine::Application app;



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
		//EditorCore coreEditor;
		//ImGuiLayer guiLayer;
		std::string sessionName = "Null";

	};
}