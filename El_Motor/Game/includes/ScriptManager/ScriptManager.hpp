#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <filesystem>
#include "ScriptRoot/Script.hpp"
#include "UserScript/UserScript.hpp"

//to proprely update and manage scripts , you need to register themp with Initilize, then call StartAll to call OnStart on all of them, and then call updateScripts every frame to call Update on all of them
class ScriptManager
{
private:
    std::vector<std::unique_ptr<UserScript>> scripts;

public:
    ScriptManager() {}
    ~ScriptManager() {}





	// Creates a new script with the given name, generating the necessary header and cpp files
	void createScript(std::string scriptName , std::string projectName);

    // Deletes a script by name, with options to delete the corresponding .cpp and .hpp files
    void DeleteScript(const std::string& projectPath,const std::string& scriptName);

    
    std::filesystem::path FindProjectRoot();


	// 
	void Restart();

    // Calls OnStart() on all registered scripts
    void StartAll();

    // Initializes the ScriptManager by creating instances of all registered scripts
    void Initialize();

    // Calls Update(deltatime) on all registered scripts
    void updateScripts(float deltatime);

    std::vector<std::unique_ptr<UserScript>>& GetScripts() { return scripts; }

};