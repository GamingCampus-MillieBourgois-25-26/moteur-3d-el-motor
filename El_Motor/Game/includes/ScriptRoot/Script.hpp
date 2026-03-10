#pragma once

/**
 * @brief Abstract base class for all user scripts.
 *
 * Scripts should inherit from this class and implement the OnStart() and Update() methods.
 * This allows the engine to call lifecycle methods on all registered scripts consistently.
 */
class Script {

public:
    /**
     * @brief Virtual destructor.
     * Ensures derived scripts are properly destroyed when deleted via a base pointer.
     */
    virtual ~Script() = default;

    /**
     * @brief Called once when the script is initialized.
     * Use this method to set up any state or references needed before the first Update().
     */
    virtual void OnStart() = 0;

    /**
     * @brief Called every frame to update the script.
     * @param deltatime Time elapsed since the last frame, in seconds.
     */
    virtual void Update(float deltatime) = 0;
};