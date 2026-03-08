#pragma once
#include "CoreEngine/CoreEngine.hpp"

namespace Runtime {

    /**
     * @brief Bridges input between GLFW and the Engine's InputManager.
     *
     * Handles fetching input from GLFW and updating the CoreEngine's input system.
     */
    class InputBridge {
    public:

        /**
         * @brief Initializes the input bridge.
         * Sets up any required internal state.
         */
        void init();

        /**
         * @brief Updates the input system for the current frame.
         * @param core Reference to the CoreEngine instance.
         * @param app Reference to the Application instance.
         */
        void update(Engine::CoreEngine& core, Engine::Application& app);

        /**
         * @brief Fetches input events directly from GLFW and updates the CoreEngine input state.
         * @param core Reference to the CoreEngine instance.
         * @param app Reference to the Application instance.
         */
        void fetchGLFWInput(Engine::CoreEngine& core, Engine::Application& app);

        /**
         * @brief Gets the current X-coordinate of the mouse.
         * @return double Mouse X position.
         */
        double getMouseX() const { return x; }

        /**
         * @brief Gets the current Y-coordinate of the mouse.
         * @return double Mouse Y position.
         */
        double getMouseY() const { return y; }

    protected:

        /// Current X position of the mouse
        double x = 0.0;

        /// Current Y position of the mouse
        double y = 0.0;

    };

}