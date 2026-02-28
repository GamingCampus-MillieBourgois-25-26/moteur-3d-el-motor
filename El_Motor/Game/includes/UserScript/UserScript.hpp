#pragma once
#include "ScriptRoot/Script.hpp"
#include <string>



class UserScript : public Script
{
protected:
	std::string name;

public:
	//Constructor and destructor
	UserScript(std::string ScriptName);
	~UserScript() = default;


	//begin play and tick functions
	void OnStart() override;
	void Update(float deltatime) override;


	//Setters
	void SetName(const std::string& newName) { name = newName; }


	//Getters
	const std::string& GetName() const { return name; }
};