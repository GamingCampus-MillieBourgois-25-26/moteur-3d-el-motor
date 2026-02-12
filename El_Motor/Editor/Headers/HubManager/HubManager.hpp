#pragma once
#include "Scene/Scene.hpp"
#include <iostream>


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