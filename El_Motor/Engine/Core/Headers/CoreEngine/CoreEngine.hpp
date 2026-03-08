#pragma once

#include "Time_Manager/TimeManager.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Input_Manager/InputManager.hpp"
#include "Logger/Logger.hpp"
#include "Application/App.hpp"
#include "Scene/Scene.hpp"
#include "Camera/EditorCamera.hpp"

namespace Engine
{

    /**
     * @brief Core class of the engine.
     *
     * Responsible for initializing systems, running the main loop,
     * and shutting down the engine properly. Provides access to
     * core subsystems like input, time, logging, assets, scenes, and camera.
     */
    class CoreEngine {
    private:

        /// Manages user input (keyboard, mouse, etc.)
        InputManager inputManager;

        /// Handles time calculations (delta time, frame timing)
        TimeManager timeManager;

        /// Handles logging and debug messages
        LoggerManager loggerManager;

        /// Manages loading and storage of engine assets
        AssetManager assetManager;

        /// Default active scene of the engine
        std::shared_ptr<Scene> defaultScene;

        /// Editor camera used for debugging or editor mode
        EditorCamera camera;

        /// Indicates whether the engine main loop is running
        bool running = false;

        /// Delta time between frames
        float dt = 0.0f;

    public:

        /// Default constructor
        CoreEngine() = default;

        /**
         * @brief Initializes the engine systems.
         *
         * @param app Reference to the application instance
         */
        void init(Engine::Application& app);

        /**
         * @brief Runs the main engine loop.
         *
         * Handles update logic, rendering, and input processing.
         */
        void run();

        /**
         * @brief Shuts down the engine and releases all resources.
         */
        void shutdown();

        /**
         * @brief Checks whether the engine is currently running.
         * @return true if the engine loop is active
         */
        bool isRunning() const { return running; }


        // =========================
        // System Getters
        // =========================

        /// @brief Returns the input manager
        InputManager& getInputManager() { return inputManager; }

        /// @brief Returns the time manager
        TimeManager& getTimeManager() { return timeManager; }

        /// @brief Returns the logger manager
        LoggerManager& getLoggerManager() { return loggerManager; }

        /// @brief Returns the asset manager
        AssetManager& getAssetManager() { return assetManager; }

        /// @brief Returns the active scene
        std::shared_ptr<Scene>& getScene() { return defaultScene; }

        /// @brief Returns the editor camera
        EditorCamera& getCamera() { return camera; }

        /// @brief Returns the delta time between frames
        float getDeltaTime() const { return dt; }


        // =========================
        // Setters
        // =========================

        /**
         * @brief Sets the active scene of the engine
         * @param scene Scene to activate
         */
        void SetScene(std::shared_ptr<Scene> scene) { defaultScene = scene; }

        /**
         * @brief Sets the delta time between frames
         * @param delta Frame delta time
         */
        void SetDeltaTime(float delta) { dt = delta; }

    };
} // namespace Engine