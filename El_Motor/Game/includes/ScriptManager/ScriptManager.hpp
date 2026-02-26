#pragma once
#include <vector>
#include <iostream>
#include <string>


class ScriptManager
{
private:
	std::vector<std::unique_ptr<UserScript*>> scripts;

public:
	ScriptManager(){}
	~ScriptManager(){}

	 
	void createScript(std::string scriptName);
	void updateScripts(float deltatime);
	void destroyScript(std::string scriptName);

};