#pragma once
#include "InputBridge/InputBridge.hpp"
#include "CoreEngine/CoreEngine.hpp"
#include "Application/App.hpp"

namespace Runtime {

    /**
     * @brief High-level runtime bridge that manages the application, engine, and input.
     *
     * This class serves as a top-level interface to initialize, run, and shut down the engine
     * and its associated systems, including input handling via InputBridge.
     */
    class Bridge {
    private:
        /// The main application instance
        Engine::Application app;

        /// The core engine instance
        Engine::CoreEngine engine;

        /// The input bridge instance for handling input events
        Runtime::InputBridge inputBridge;

    public:

        /**
         * @brief Initializes the runtime bridge.
         * Sets up the application, engine, and input system.
         */
        void init();

        /**
         * @brief Runs the main loop of the engine.
         * Continuously updates input, time, and the current scene.
         */
        void run();

        /**
         * @brief Shuts down the engine and application cleanly.
         * Releases resources and cleans up subsystems.
         */
        void shutdown();

        /**
         * @brief Checks if the application window should close.
         * @return true if the window should close, false otherwise.
         */
        bool shouldClose() const { return app.windowOpener->getMyWindow(); }

    };

}