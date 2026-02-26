#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <filesystem>
#include "ScriptRoot/Script.hpp"


class ScriptManager
{
private:
	std::vector<std::unique_ptr<Script>> scripts;

public:
	ScriptManager(){}
	~ScriptManager(){}


	void createScript(std::string scriptName , std::filesystem::path& directory);

	void StartAll();


	void updateScripts(float deltatime);

	void destroyScript(std::string scriptName);

	void RegisterScript(std::unique_ptr<Script> script);

	std::vector<std::unique_ptr<Script>>& GetScripts() { return scripts; }
	
};