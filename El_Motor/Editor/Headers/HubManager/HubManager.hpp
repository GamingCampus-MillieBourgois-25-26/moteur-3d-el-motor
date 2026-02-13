#pragma once

#include <iostream>
#include "Window/Window.hpp"

namespace Editor {
	class HubManager
	{
	public:

		HubManager();
		~HubManager();


		//Functions
		void Init();
		void CreateScene();
		void LoadScene();



		//Getters
		std::string GetSessionName() const { return sessionName; }



		//Setters
		void SetSessionName(std::string name) { sessionName = name; }

	private:


		//Variables
		std::string sessionName = "Null";
	};
}