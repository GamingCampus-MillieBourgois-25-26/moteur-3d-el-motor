#pragma once
#include <functional>
#include <vector>
#include <memory>

class UserScript;

/**
 * @brief Singleton registry that manages user script factories and can instantiate scripts on demand.
 *
 * This registry allows scripts to register a factory function that creates instances of UserScript.
 * It is used by the ScriptManager to initialize and manage all user scripts.
 */
class ScriptRegistry
{
public:
    /// @brief Type alias for a factory function that returns a unique_ptr to a UserScript
    using ScriptFactory = std::function<std::unique_ptr<UserScript>()>;

    /**
     * @brief Returns the singleton instance of the ScriptRegistry.
     * @return Reference to the singleton ScriptRegistry
     */
    static ScriptRegistry& Instance();

    /**
     * @brief Registers a script factory function.
     *
     * The factory function should create and return a new instance of a UserScript.
     * @param factory A function that creates a new UserScript
     */
    void Register(ScriptFactory factory);

    /**
     * @brief Creates instances of all registered scripts.
     *
     * Calls each registered factory function and collects the resulting UserScript instances
     * into a vector, which is returned to the caller.
     * @return Vector of unique_ptr<UserScript> containing all instantiated scripts
     */
    std::vector<std::unique_ptr<UserScript>> CreateAll();

private:
    /// @brief Internal storage of all registered script factory functions
    std::vector<ScriptFactory> factories;
};