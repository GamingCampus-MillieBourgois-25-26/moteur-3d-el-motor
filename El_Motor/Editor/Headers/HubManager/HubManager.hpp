#pragma once
#include <iostream>
#include "EditCore/EditCore.hpp"
#include "ImGuiLayer/ImGuiLayer.hpp"
#include "Application/App.hpp"
#include "GuiToolBarPanel/Buttons.hpp"
#include "ScriptManager/ScriptManager.hpp"
#include "Camera/EditorCamera.hpp"
#include "API_Sound/MiniAudioSystem.hpp"
#include <vector>

namespace Editor {

    /**
     * @brief Main hub manager for the El Motor editor.
     *
     * Handles overall editor state, UI rendering, and transitions between different editor modes.
     * Coordinates between the GUI layer, the core editor, and asset/script managers.
     */
    class HubManager {
    protected:
        /**
         * @brief Enumeration of the different states the editor can be in.
         *
         * Controls which UI and functionality is active and displayed.
         */
        enum EditorState {
            Hub,    ///< Project selection and creation hub
            Editor, ///< Main editor for scene and GameObject editing
            Run     ///< Game runtime/play mode
        };

        /// Application instance managing window and rendering
        Engine::Application app;

    private:
        /// UI button panel manager
        Buttons buttons;

        /// Core editor with scene editing functionality
        EditorCore coreEditor;

        /// GUI layer for ImGui rendering
        GuiLayer guiLayer;

        /// Current editor state (Hub, Editor, or Run)
        EditorState editorState = Hub;

        /// Logger for debug output
        Engine::LoggerManager logger;

        /// Script manager for project scripts
        ScriptManager scriptManager;

        /// Camera for the editor
        EditorCamera camera;

    public:
        /// @brief Constructor for HubManager
        HubManager();

        /// @brief Destructor for HubManager
        ~HubManager();

        /// @brief Shuts down the editor hub and cleans up resources
        void Shutdown();

        /// @brief Initializes the editor hub including the application, GUI layer, and systems
        void Init();

        /// @brief Main editor loop. Runs until the window is closed.
        /// Handles rendering, input, and state transitions
        void HubRun();

        /// @brief Initializes a new project in the editor
        void CreateProject();

        /// @brief Loads an existing project into the editor
        void LoadProject();

        /// @brief Renders the hub UI for project selection and creation
        void DrawHubUI();

        /// @brief Renders the main editor UI for scene and GameObject editing
        void DrawEditorUI();

        /// @brief Gets the current editor state
        /// @return Reference to the current EditorState
        EditorState& GetEditorState() { return editorState; }

        /// @brief Sets the current editor state
        /// @param state The new editor state
        void SetEditorState(EditorState state) { editorState = state; }
    };

} // namespace Editor