#pragma once
#include "ScriptRoot/Script.hpp"
#include <string>

/**
 * @brief Represents a user-defined script that can be attached to game objects.
 *
 * Inherits from the abstract base class Script. Provides a name and implements
 * the OnStart and Update lifecycle methods, which are called by the ScriptManager.
 */
class UserScript : public Script
{
protected:
    /// The name of the script
    std::string name;

public:
    /**
     * @brief Constructs a new UserScript with the given name.
     * @param ScriptName The name to assign to this script.
     */
    UserScript(std::string ScriptName);

    /**
     * @brief Default destructor.
     */
    ~UserScript() = default;

    /**
     * @brief Called once when the script starts.
     * Override this to initialize state or references needed by the script.
     */
    void OnStart() override;

    /**
     * @brief Called every frame to update the script logic.
     * @param deltatime Time elapsed since the last frame, in seconds.
     */
    void Update(float deltatime) override;

    /**
     * @brief Sets the name of the script.
     * @param newName New name to assign.
     */
    void SetName(const std::string& newName) { name = newName; }

    /**
     * @brief Gets the name of the script.
     * @return const std::string& The current name of the script.
     */
    const std::string& GetName() const { return name; }
};