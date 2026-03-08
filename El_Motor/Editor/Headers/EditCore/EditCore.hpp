#pragma once
#include "CoreEngine/CoreEngine.hpp"
#include "Application/App.hpp"

namespace Editor {

    /**
     * @brief Manages the core of the editor.
     *
     * Coordinates initialization, execution, and shutdown of the editor,
     * as well as user input handling and the graphics engine.
     */
    class EditorCore {
    private:
        /// Main graphics engine of the editor
        Engine::CoreEngine coreEngine;

        /// Mouse X position in editor space
        double x = 0.0;

        /// Mouse Y position in editor space
        double y = 0.0;

    protected:
        // Reserved for protected members

    public:
        /// @brief Default constructor
        EditorCore() {}

        /// @brief Destructor
        ~EditorCore() {}

        /**
         * @brief Initializes the editor and its components.
         * @param app Reference to the main application
         */
        void editorInit(Engine::Application& app);

        /**
         * @brief Main execution loop of the editor.
         * @param app Reference to the main application
         */
        void editorRun(Engine::Application& app);

        /**
         * @brief Shuts down the editor and releases resources.
         */
        void editorShutdown();

        /**
         * @brief Starts the runtime mode of the game/project.
         */
        void startRuntime();

        /**
         * @brief Updates user input (keyboard, mouse, etc.).
         * @param app Reference to the main application
         */
        void InputUpdate(Engine::Application& app);

        /**
         * @brief Gets the current mouse X position in the editor.
         * @return Mouse X coordinate
         */
        double getMouseEditorX() const { return x; }

        /**
         * @brief Gets the current mouse Y position in the editor.
         * @return Mouse Y coordinate
         */
        double getMouseEditorY() const { return y; }

        /**
         * @brief Accesses the main graphics engine.
         * @return Non-const reference to the core engine
         */
        Engine::CoreEngine& GetEngine() { return coreEngine; }
    };

}