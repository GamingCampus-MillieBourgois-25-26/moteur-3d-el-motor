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

    /// <summary>
    /// Core class of the engine.
    /// Responsible for initializing systems, running the main loop,
    /// and shutting down the engine properly.
    /// </summary>
    class CoreEngine {
    private:

        /// <summary>
        /// Manages user input (keyboard, mouse, etc.)
        /// </summary>
        InputManager inputManager;

        /// <summary>
        /// Handles time calculations (delta time, frame timing)
        /// </summary>
        TimeManager timeManager;

        /// <summary>
        /// Handles logging and debug messages
        /// </summary>
        LoggerManager loggerManager;

        /// <summary>
        /// Manages loading and storage of engine assets
        /// </summary>
        AssetManager assetManager;

        /// <summary>
        /// Default active scene of the engine
        /// </summary>
        std::shared_ptr<Scene> defaultScene;

        /// <summary>
        /// Editor camera used for debugging or editor mode
        /// </summary>
        EditorCamera camera;

        /// <summary>
        /// Indicates whether the engine main loop is running
        /// </summary>
        bool running = false;

        /// <summary>
        /// Delta time between frames
        /// </summary>
        float dt = 0.0f;

    public:

        /// <summary>
        /// Default constructor
        /// </summary>
        CoreEngine() = default;

        /// <summary>
        /// Initializes the engine systems.
        /// </summary>
        /// <param name="app">Reference to the application instance</param>
        void init(Engine::Application& app);

        /// <summary>
        /// Runs the main engine loop.
        /// Handles update logic, rendering, and input processing.
        /// </summary>
        void run();

        /// <summary>
        /// Shuts down the engine and releases resources.
        /// </summary>
        void shutdown();

        /// <summary>
        /// Checks whether the engine is currently running.
        /// </summary>
        /// <returns>True if the engine loop is active</returns>
        bool isRunning() const { return running; }


        // =========================
        // System Getters
        // =========================

        /// <summary>
        /// Returns the input manager.
        /// </summary>
        InputManager& getInputManager() { return inputManager; }

        /// <summary>
        /// Returns the time manager.
        /// </summary>
        TimeManager& getTimeManager() { return timeManager; }

        /// <summary>
        /// Returns the logger manager.
        /// </summary>
        LoggerManager& getLoggerManager() { return loggerManager; }

        /// <summary>
        /// Returns the asset manager.
        /// </summary>
        AssetManager& getAssetManager() { return assetManager; }

        /// <summary>
        /// Returns the active scene.
        /// </summary>
        std::shared_ptr<Scene>& getScene() { return defaultScene; }

        /// <summary>
        /// Returns the editor camera.
        /// </summary>
        EditorCamera& getCamera() { return camera; }

        /// <summary>
        /// Returns the delta time between frames.
        /// </summary>
        float getDeltaTime() const { return dt; }


        // =========================
        // Setters
        // =========================

        /// <summary>
        /// Sets the active scene of the engine.
        /// </summary>
        /// <param name="scene">Scene to activate</param>
        void SetScene(std::shared_ptr<Scene> scene) { defaultScene = scene; }

        /// <summary>
        /// Sets the delta time between frames.
        /// </summary>
        /// <param name="delta">Frame delta time</param>
        void SetDeltaTime(float delta) { dt = delta; }

    };
}