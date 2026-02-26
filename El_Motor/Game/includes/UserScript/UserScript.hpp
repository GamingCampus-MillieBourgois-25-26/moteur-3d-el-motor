#pragma once

#include "ScriptRoot/Script.hpp"
#include <string>



class UserScript : public Script
{
private:
	std::string name;

public:
	//Constructor and destructor
	UserScript(std::string ScriptName);
	~UserScript() = default;


	//begin play and tick functions
	void OnStart() override;
	void Update(float deltatime) override;


	//Setters
	void SetName(std::string newName) { name = newName; }


	//Getters
	std::string GetName() const { return name; }
};