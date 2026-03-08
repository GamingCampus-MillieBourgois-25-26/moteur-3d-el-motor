#pragma once
#include "Scene/Scene.hpp"
#include "Entity/GameObject.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "API_Sound/MiniAudioSystem.hpp"
#include "Assets/Asset.hpp"
#include <string>
#include <filesystem>

struct ImVec2;
class GameObject;
class Asset;
class AssetManager;
class ScriptManager;

namespace Editor
{
	/// <summary>
	/// Class responsible for handling editor UI buttons and interactions.
	/// Manages project creation/loading, GameObject manipulation,
	/// component management, script handling, audio control,
	/// and project saving inside the editor.
	/// </summary>
	class Buttons
	{
	private:

		/// Indicates whether the project loading dialog is open
		bool LoadProjectDial = false;

		/// Indicates whether the project is ready to be loaded
		bool LoadProjReady = false;

		/// Indicates whether an asset loading operation is requested
		bool LoadAsset = false;

		/// Name of the current editor session / project
		std::string sessionName = "Null";

		/// Status message associated with the session name input
		std::string sessionNameStatus = "Type a project name, then press Enter to confirm";

		/// Path to the currently loaded project
		std::string projectPath = "Null";

	protected:

		/// Pointer to the currently selected GameObject
		Engine::GameObject* selectedEntity = nullptr;

		/// Label of the currently selected GameObject
		std::string currentEntityLabel;

		/// Name of the currently selected script
		std::string selectedScript;

		/// Name of the script being created or edited
		std::string scriptName = "Null";

		/// Pointer to the currently selected component
		Engine::Component* selectedComponent = nullptr;

	public:

		/// <summary>
		/// Default constructor
		/// </summary>
		Buttons() {};

		/// <summary>
		/// Destructor
		/// Clears pointers to the selected entity and component
		/// </summary>
		~Buttons() {
			selectedEntity = nullptr;
			selectedComponent = nullptr;
			delete selectedComponent;
			delete selectedEntity;
		};

		/// <summary>
		/// Initializes the editor buttons and UI states
		/// </summary>
		void init();

		/// <summary>
		/// Updates editor button logic and interactions
		/// </summary>
		/// <param name="manager">Asset manager used by the editor</param>
		void update(AssetManager& manager);

		// =========================
		// Project / Hub Buttons
		// =========================

		/// <summary>
		/// Creates a new project
		/// </summary>
		/// <returns>True if the project was successfully created</returns>
		bool createProject();

		/// <summary>
		/// Loads an existing project
		/// </summary>
		void loadProject();

		/// <summary>
		/// Handles project name input and validation
		/// </summary>
		void projectName();

		// =========================
		// Script Buttons
		// =========================

		/// <summary>
		/// Displays the script management menu
		/// </summary>
		/// <param name="scriptM">Script manager</param>
		void showScriptMenu(ScriptManager& scriptM);

		/// <summary>
		/// Adds a new script
		/// </summary>
		/// <param name="scriptM">Script manager</param>
		void AddScript(ScriptManager& scriptM);

		/// <summary>
		/// Deletes an existing script
		/// </summary>
		/// <param name="scriptM">Script manager</param>
		void deleteScript(ScriptManager& scriptM);

		/// <summary>
		/// Opens a script for editing
		/// </summary>
		/// <param name="scriptM">Script manager</param>
		void editScript(ScriptManager& scriptM);

		/// <summary>
		/// Displays the list of available scripts
		/// </summary>
		/// <param name="scriptM">Script manager</param>
		void showScripts(ScriptManager& scriptM);

		/// <summary>
		/// Checks whether the script name is valid
		/// </summary>
		/// <param name="str">Script name to validate</param>
		/// <returns>True if the script name is valid</returns>
		bool CheckScriptNameValid(const std::string& str);

		/// <summary>
		/// Reloads editor scripts
		/// </summary>
		/// <returns>True if the reload succeeded</returns>
		bool reloadScript();

		// =========================
		// GameObject Buttons
		// =========================

		/// <summary>
		/// Selects a GameObject from the scene
		/// </summary>
		/// <param name="scene">Active scene</param>
		void selectGO(std::shared_ptr<Engine::Scene>& scene);

		/// <summary>
		/// Creates a new GameObject in the scene
		/// </summary>
		/// <param name="scene">Active scene</param>
		void createGO(std::shared_ptr<Engine::Scene>& scene);

		/// <summary>
		/// Deletes the selected GameObject from the scene
		/// </summary>
		/// <param name="scene">Active scene</param>
		void delGO(std::shared_ptr<Engine::Scene>& scene);

		/// <summary>
		/// Changes the name of the selected GameObject
		/// </summary>
		void ChangeGOName();

		/// <summary>
		/// Checks whether the GameObject name is valid
		/// </summary>
		/// <param name="str">Name to validate</param>
		/// <returns>True if the name is not composed only of spaces</returns>
		bool CheckGoNameValid(const std::string& str);

		/// <summary>
		/// Checks whether the characters used in a name are valid
		/// </summary>
		/// <param name="str">String to validate</param>
		/// <returns>True if characters are valid</returns>
		bool CheckCaraterValid(const std::string& str);

		// =========================
		// Component Buttons
		// =========================

		/// <summary>
		/// Displays all components attached to the selected GameObject
		/// </summary>
		/// <param name="assetM">Asset manager</param>
		void showCmpnt(const AssetManager& assetM);

		/// <summary>
		/// Adds a component to the selected GameObject
		/// </summary>
		void addComponent();

		/// <summary>
		/// Deletes a component from the selected GameObject
		/// </summary>
		void delComponent();

		/// <summary>
		/// Edits the selected component values
		/// </summary>
		/// <param name="assetM">Asset manager</param>
		void editComponent(const AssetManager& assetM);

		// =========================
		// Sound Buttons
		// =========================

		/// <summary>
		/// Loads a sound file into the audio system
		/// </summary>
		/// <param name="sound">MiniAudio sound system</param>
		void loadSound(Engine::MiniAudioSystem sound);

		/// <summary>
		/// Plays a loaded sound
		/// </summary>
		/// <param name="sound">MiniAudio sound system</param>
		void playSound(Engine::MiniAudioSystem sound);

		/// <summary>
		/// Stops the currently playing sound
		/// </summary>
		/// <param name="sound">MiniAudio sound system</param>
		void stopPlayingSound(Engine::MiniAudioSystem sound);

		// =========================
		// Gizmo
		// =========================

		/// <summary>
		/// Handles editor gizmo manipulation (translate/rotate/scale)
		/// </summary>
		void Guizmo();

		// =========================
		// Project Saving
		// =========================

		/// <summary>
		/// Saves the current project
		/// </summary>
		/// <returns>True if the project was successfully saved</returns>
		bool saveProject();

		/// <summary>
		/// Starts the runtime mode of the editor
		/// </summary>
		/// <returns>True if runtime started successfully</returns>
		bool startRuntime();

		/// <summary>
		/// Loads project assets
		/// </summary>
		/// <param name="manager">Asset manager</param>
		void loadAssets(AssetManager& manager);

		// =========================
		// Getters
		// =========================

		/// <summary>
		/// Returns the current session name
		/// </summary>
		/// <returns>Session name</returns>
		std::string GetSessionName() const { return sessionName; }

		/// <summary>
		/// Returns the session status message
		/// </summary>
		/// <returns>Status message</returns>
		std::string GetSessionNameStatus() const { return sessionNameStatus; }

		/// <summary>
		/// Indicates whether the project load dialog is active
		/// </summary>
		/// <returns>True if active</returns>
		bool GetLoadProject() const { return LoadProjectDial; }

		/// <summary>
		/// Returns the current project path
		/// </summary>
		/// <returns>Project path</returns>
		std::string GetProjectPath() const { return projectPath; }

		/// <summary>
		/// Indicates if the project is ready to be loaded
		/// </summary>
		/// <returns>True if ready</returns>
		bool GetLoadProjReady() const { return LoadProjReady; }

		/// <summary>
		/// Indicates if asset loading is requested
		/// </summary>
		/// <returns>True if assets should be loaded</returns>
		bool GetLoadAsset() const { return LoadAsset; }

		/// <summary>
		/// Returns the current script name
		/// </summary>
		/// <returns>Script name</returns>
		std::string GetScriptName() const { return scriptName; }

		// =========================
		// Setters
		// =========================

		/// <summary>
		/// Sets the session name
		/// </summary>
		void SetSessionName(std::string session) { sessionName = session; }

		/// <summary>
		/// Sets the session status message
		/// </summary>
		void SetSessionNameStatus(std::string txt) { sessionNameStatus = txt; }

		/// <summary>
		/// Enables or disables the load session dialog
		/// </summary>
		void SetLoadSession(bool activated) { LoadProjectDial = activated; }

		/// <summary>
		/// Sets the project path
		/// </summary>
		void SetProjectPath(std::string path) { projectPath = path; }

		/// <summary>
		/// Sets the project ready state
		/// </summary>
		void SetLoadProjReady(bool ready) { LoadProjReady = ready; }

		/// <summary>
		/// Enables or disables asset loading
		/// </summary>
		void SetLoadAsset(bool load) { LoadAsset = load; }

		/// <summary>
		/// Sets the script name
		/// </summary>
		void SetScriptName(std::string name) { scriptName = name; }

		/// <summary>
		/// Clears the selected entity
		/// </summary>
		void SetSelectedEntity() { selectedEntity = nullptr; }
	};
}