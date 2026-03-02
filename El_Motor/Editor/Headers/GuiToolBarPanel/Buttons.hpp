#pragma once
#include "Scene/Scene.hpp"
#include "Entity/GameObject.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Assets/Asset.hpp"
#include <string>
#include <filesystem>

class ScriptManager;
namespace Editor
{
	// GO = GameObject
	class Buttons
	{
	private:

		//Bool
		bool LoadProjectDial = false;
		bool LoadProjReady = false;
		bool LoadAsset = false;
		//Session name / error
		std::string sessionName = "Null";
		std::string sessionNameStatus = "Type a project name, then press Enter to confirm";
		std::string projectPath = "Null";

	protected:
		//Selected Entity pointeur + label
		Engine::GameObject* selectedEntity = nullptr;
		std::string currentEntityLabel;
		std::string selectedScript;

		//Selected Component pointer
		Engine::Component* selectedComponent = nullptr;

		
	public:
		Buttons() {};
		~Buttons() {
			delete selectedEntity;
			delete selectedComponent;
		};

		void init();
		void update(AssetManager& manager);
		
		//Hub Buttons
		bool createProject();
		void loadProject();
		void projectName();
		
		//Script Buttons
		void showScriptMenu(ScriptManager& scriptM);
		void AddScript(ScriptManager& scriptM , std::string name);
		void deleteScript(ScriptManager& scriptM) const;
		void editScript(ScriptManager& scriptM);
		void showScripts(ScriptManager& scriptM);
		bool CheckScriptNameValid(const std::string& str, bool IsCpp);
		bool reloadScript();

		//Editor Entity Buttons
		void selectGO(std::shared_ptr<Engine::Scene>& scene);//select GO
		void createGO(std::shared_ptr<Engine::Scene>& scene);//create GO
		void delGO(std::shared_ptr<Engine::Scene>& scene);// delete GO
		void ChangeGOName();//Change the name of the GO selected
		bool CheckGoNameValid(const std::string& str);//Check if the GO name isn't only composed of spaces
		bool CheckCaraterValid(const std::string& str);


		//Editor Component Buttons
		void showCmpnt(const AssetManager& assetM);//show all the component of a selected GO
		void addComponent(); //add a component to a selecte GO
		void delComponent(); //delete a component of a selected GO
		void editComponent(const AssetManager& assetM); //Change the value of the selected Go Transform

		//Editor save level
		bool saveProject();


		bool startRuntime();
		void loadAssets(AssetManager& manager);

		//Getter
		std::string GetSessionName() const { return sessionName; }
		std::string GetSessionNameStatus() const { return sessionNameStatus; }
		bool GetLoadProject() const { return LoadProjectDial; }
		std::string GetProjectPath() const {return projectPath;}
		bool GetLoadProjReady() const { return LoadProjReady; }
		bool GetLoadAsset() const { return LoadAsset; }
		//Setter
		void SetSessionName(std::string session) { sessionName = session; }
		void SetSessionNameStatus(std::string txt) { sessionNameStatus = txt; }
		void SetLoadSession(bool activated) { LoadProjectDial = activated; }
		void SetProjectPath(std::string path) { projectPath = path; }
		void SetLoadProjReady(bool ready) { LoadProjReady = ready; }
		void SetLoadAsset(bool load) { LoadAsset = load; }
	};
}