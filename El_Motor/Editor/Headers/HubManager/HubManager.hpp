#pragma once
#include <iostream>
#include "EditCore/EditCore.hpp"
#include "ImGuiLayer/ImGuiLayer.hpp"
#include "Application/App.hpp"
#include "GuiToolBarPanel/Buttons.hpp"
#include "ScriptManager/ScriptManager.hpp"
#include "Camera/EditorCamera.hpp"
#include <vector>

namespace Editor
{
	/// <summary>
	/// Main hub manager for the El Motor editor.
	/// Manages overall editor state, UI rendering, and transitions between different editor modes.
	/// Coordinates between the GUI layer, the core editor, and the asset/script managers.
	/// </summary>
	class HubManager
	{
	protected:
		/// <summary>
		/// Enumeration defining the different states the editor can be in.
		/// Controls which UI and functionality is displayed and active.
		/// </summary>
		enum EditorState
		{
			Hub,	///< Project selection and creation hub
			Editor, ///< Main editor for scene and GameObject editing
			Run		///< Game runtime/play mode
		};

		/// <summary>
		/// The application instance managing window and rendering.
		/// </summary>
		Engine::Application app;

	private:
		/// <summary>
		/// UI button panel manager.
		/// </summary>
		Buttons buttons;

		/// <summary>
		/// The core editor with scene editing functionality.
		/// </summary>
		EditorCore coreEditor;

		/// <summary>
		/// GUI layer for ImGui rendering.
		/// </summary>
		GuiLayer guiLayer;

		/// <summary>
		/// Current editor state (Hub, Editor, or Run).
		/// </summary>
		EditorState editorState = Hub;

		/// <summary>
		/// Logger for debug output.
		/// </summary>
		Engine::LoggerManager logger;

		/// <summary>
		/// Script manager for project scripts.
		/// </summary>
		ScriptManager scriptManager;

	public:
		/// <summary>
		/// Constructor for HubManager.
		/// </summary>
		HubManager();

		/// <summary>
		/// Destructor for HubManager.
		/// </summary>
		~HubManager();

		/// <summary>
		/// Initializes the editor hub including the application, GUI layer, and systems.
		/// Must be called before HubRun().
		/// </summary>
		void Init();

		/// <summary>
		/// Main editor loop. Runs until the window is closed.
		/// Handles rendering, input, and state transitions.
		/// </summary>
		void HubRun();

		/// <summary>
		/// Initializes a new project in the editor.
		/// </summary>
		void CreateProject();

		/// <summary>
		/// Loads an existing project into the editor.
		/// </summary>
		void LoadProject();

		/// <summary>
		/// Renders the hub UI for project selection and creation.
		/// </summary>
		void DrawHubUI();

		/// <summary>
		/// Renders the main editor UI for scene and GameObject editing.
		/// </summary>
		void DrawEditorUI();

		/// <summary>
		/// Gets the current editor state.
		/// </summary>
		/// <returns>Reference to the current EditorState</returns>
		EditorState& GetEditorState() { return editorState; }

		/// <summary>
		/// Sets the current editor state.
		/// </summary>
		/// <param name="state">The new editor state</param>
		void SetEditorState(EditorState state) { editorState = state; }






	};
}