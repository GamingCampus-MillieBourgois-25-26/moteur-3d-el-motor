#pragma once
#include <functional>
#include <vector>
#include <memory>

class UserScript;

class ScriptRegistry
{
public:
    using ScriptFactory = std::function<std::unique_ptr<UserScript>()>;

    static ScriptRegistry& Instance();

	// Registers a script factory function that creates an instance of a Script
    void Register(ScriptFactory factory);

	// Creates instances of all registered scripts and returns them in a vector
    std::vector<std::unique_ptr<UserScript>> CreateAll();

private:
    std::vector<ScriptFactory> factories;
};