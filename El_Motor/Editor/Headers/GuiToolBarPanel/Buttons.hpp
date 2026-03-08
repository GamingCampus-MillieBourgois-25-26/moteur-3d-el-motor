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

namespace Editor {

    /**
     * @brief Handles editor UI buttons and interactions.
     *
     * Manages project creation/loading, GameObject manipulation,
     * component management, script handling, audio control,
     * and project saving inside the editor.
     */
    class Buttons {
    private:
        /// Whether the project load dialog is open
        bool LoadProjectDial = false;

        /// Whether the project is ready to load
        bool LoadProjReady = false;

        /// Whether an asset loading operation is requested
        bool LoadAsset = false;

        /// Current editor session/project name
        std::string sessionName = "Null";

        /// Status message for session name input
        std::string sessionNameStatus = "Type a project name, then press Enter to confirm";

        /// Path of the current project
        std::string projectPath = "Null";

    protected:
        /// Pointer to the selected GameObject
        Engine::GameObject* selectedEntity = nullptr;

        /// Label of the selected GameObject
        std::string currentEntityLabel;

        /// Name of the selected script
        std::string selectedScript;

        /// Name of the script being created or edited
        std::string scriptName = "Null";

        /// Pointer to the selected component
        Engine::Component* selectedComponent = nullptr;

    public:
        /// @brief Default constructor
        Buttons() {}

        /// @brief Destructor, clears selected pointers
        ~Buttons() {
            selectedEntity = nullptr;
            selectedComponent = nullptr;
            delete selectedComponent;
            delete selectedEntity;
        }

        /// @brief Initializes editor buttons and UI states
        void init();

        /// @brief Updates editor button logic and interactions
        /// @param manager Reference to the asset manager
        void update(AssetManager& manager);

        // =========================
        // Project / Hub Buttons
        // =========================

        /// @brief Creates a new project
        /// @return True if project creation succeeded
        bool createProject();

        /// @brief Loads an existing project
        void loadProject();

        /// @brief Handles project name input and validation
        void projectName();

        // =========================
        // Script Buttons
        // =========================

        /// @brief Displays the script management menu
        /// @param scriptM Reference to the ScriptManager
        void showScriptMenu(ScriptManager& scriptM);

        /// @brief Adds a new script
        /// @param scriptM Reference to the ScriptManager
        void AddScript(ScriptManager& scriptM);

        /// @brief Deletes an existing script
        /// @param scriptM Reference to the ScriptManager
        void deleteScript(ScriptManager& scriptM);

        /// @brief Opens a script for editing
        /// @param scriptM Reference to the ScriptManager
        void editScript(ScriptManager& scriptM);

        /// @brief Displays the list of available scripts
        /// @param scriptM Reference to the ScriptManager
        void showScripts(ScriptManager& scriptM);

        /// @brief Checks if the script name is valid
        /// @param str Script name
        /// @return True if the name is valid
        bool CheckScriptNameValid(const std::string& str);

        /// @brief Reloads editor scripts
        /// @return True if reload succeeded
        bool reloadScript();

        // =========================
        // GameObject Buttons
        // =========================

        /// @brief Selects a GameObject from the scene
        /// @param scene Reference to the current scene
        void selectGO(std::shared_ptr<Engine::Scene>& scene);

        /// @brief Creates a new GameObject in the scene
        /// @param scene Reference to the current scene
        void createGO(std::shared_ptr<Engine::Scene>& scene);

        /// @brief Deletes the selected GameObject
        /// @param scene Reference to the current scene
        void delGO(std::shared_ptr<Engine::Scene>& scene);

        /// @brief Changes the name of the selected GameObject
        void ChangeGOName();

        /// @brief Checks if a GameObject name is valid
        /// @param str Name to check
        /// @return True if valid
        bool CheckGoNameValid(const std::string& str);

        /// @brief Checks if characters used in a name are valid
        /// @param str String to check
        /// @return True if characters are valid
        bool CheckCaraterValid(const std::string& str);

        // =========================
        // Component Buttons
        // =========================

        /// @brief Shows all components attached to the selected GameObject
        /// @param assetM Reference to the AssetManager
        void showCmpnt(const AssetManager& assetM);

        /// @brief Adds a component to the selected GameObject
        void addComponent();

        /// @brief Deletes a component from the selected GameObject
        void delComponent();

        /// @brief Edits the selected component values
        /// @param assetM Reference to the AssetManager
        void editComponent(const AssetManager& assetM);

        // =========================
        // Sound Buttons
        // =========================

        /// @brief Loads a sound file into the audio system
        /// @param sound Reference to the MiniAudioSystem
        void loadSound(Engine::MiniAudioSystem sound);

        /// @brief Plays a loaded sound
        /// @param sound Reference to the MiniAudioSystem
        void playSound(Engine::MiniAudioSystem sound);

        /// @brief Stops the currently playing sound
        /// @param sound Reference to the MiniAudioSystem
        void stopPlayingSound(Engine::MiniAudioSystem sound);

        // =========================
        // Gizmo
        // =========================

        /// @brief Handles editor gizmo manipulation (translate/rotate/scale)
        void Guizmo();

        // =========================
        // Project Saving
        // =========================

        /// @brief Saves the current project
        /// @return True if saved successfully
        bool saveProject();

        /// @brief Starts the runtime mode of the editor
        /// @return True if runtime started successfully
        bool startRuntime();

        /// @brief Loads project assets
        /// @param manager Reference to the AssetManager
        void loadAssets(AssetManager& manager);

        // =========================
        // Getters
        // =========================

        std::string GetSessionName() const { return sessionName; }
        std::string GetSessionNameStatus() const { return sessionNameStatus; }
        bool GetLoadProject() const { return LoadProjectDial; }
        std::string GetProjectPath() const { return projectPath; }
        bool GetLoadProjReady() const { return LoadProjReady; }
        bool GetLoadAsset() const { return LoadAsset; }
        std::string GetScriptName() const { return scriptName; }

        // =========================
        // Setters
        // =========================

        void SetSessionName(std::string session) { sessionName = session; }
        void SetSessionNameStatus(std::string txt) { sessionNameStatus = txt; }
        void SetLoadSession(bool activated) { LoadProjectDial = activated; }
        void SetProjectPath(std::string path) { projectPath = path; }
        void SetLoadProjReady(bool ready) { LoadProjReady = ready; }
        void SetLoadAsset(bool load) { LoadAsset = load; }
        void SetScriptName(std::string name) { scriptName = name; }
        void SetSelectedEntity() { selectedEntity = nullptr; }
    };

} // namespace Editor