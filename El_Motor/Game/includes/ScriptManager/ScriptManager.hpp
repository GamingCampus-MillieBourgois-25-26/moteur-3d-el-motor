#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <filesystem>
#include "ScriptRoot/Script.hpp"
#include "UserScript/UserScript.hpp"

/**
 * @brief Manages user scripts, including creation, deletion, initialization, starting, and updating.
 *
 * To properly update and manage scripts:
 * 1. Register scripts with Initialize()
 * 2. Call StartAll() to invoke OnStart() on all scripts
 * 3. Call updateScripts() each frame to invoke Update(deltaTime) on all scripts
 */
class ScriptManager
{
private:
    /// @brief Container holding all user scripts as unique pointers
    std::vector<std::unique_ptr<UserScript>> scripts;

public:
    /// @brief Default constructor
    ScriptManager() {}

    /// @brief Destructor
    ~ScriptManager() {}

    /**
     * @brief Creates a new script with the given name, generating the required header and cpp files.
     * @param scriptName The name of the script to create
     * @param projectName The name of the project in which to create the script
     */
    void createScript(std::string scriptName, std::string projectName);

    /**
     * @brief Deletes a script by name, optionally removing the corresponding .cpp and .hpp files.
     * @param projectPath The path of the project containing the script
     * @param scriptName The name of the script to delete
     */
    void DeleteScript(const std::string& projectPath, const std::string& scriptName);

    /**
     * @brief Restarts all scripts, typically by reinitializing or clearing existing state.
     */
    void Restart();

    /**
     * @brief Calls OnStart() on all registered scripts.
     */
    void StartAll();

    /**
     * @brief Initializes the ScriptManager by creating instances of all registered scripts.
     */
    void Initialize();

    /**
     * @brief Updates all scripts by calling Update(deltaTime) on each.
     * @param deltatime The delta time since the last update (in seconds)
     */
    void updateScripts(float deltatime);

    /**
     * @brief Returns a reference to the vector of scripts.
     * @return Reference to the internal vector of unique_ptr<UserScript>
     */
    std::vector<std::unique_ptr<UserScript>>& GetScripts() { return scripts; }
};