#pragma once
#include "Scene/Scene.hpp"
#include "Entity/GameObject.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Assets/Asset.hpp"
#include <string>
#include <filesystem>

namespace Editor
{
	// GO = GameObject
	class Buttons
	{
	private:

		//Bool
		bool LoadProjectDial = false;
		bool LoadReady = false;
		//Session name / error
		std::string sessionName = "Null";
		std::string sessionNameStatus = "Type a project name, then press Enter to confirm";
		std::string projectPath = "Null";

	protected:
		//Selected Entity pointeur + label
		Engine::GameObject* selectedEntity = nullptr;
		std::string currentEntityLabel;

		//Selected Component pointer
		Engine::Component* selectedComponent = nullptr;



		
	public:
		Buttons() {};
		~Buttons() {
			delete selectedEntity;
			delete selectedComponent;
		};

		void init();
		
		//Hub Buttons
		bool createProject();
		void loadProject();
		void projectName();
		



		//Editor Entity Buttons
		void selectGO(std::shared_ptr<Engine::Scene>& scene);//select GO
		void createGO(std::shared_ptr<Engine::Scene>& scene);//create GO
		void delGO(std::shared_ptr<Engine::Scene>& scene);// delete GO
		void ChangeGOName();//Change the name of the GO selected
		bool CheckGoNameValid(const std::string& str);//Check if the GO name isn't only composed of spaces

		//Editor Component Buttons
		void showCmpnt();//show all the component of a selected GO
		void addComponent(); //add a component to a selecte GO
		void delComponent(); //delete a component of a selected GO
		void editComponent(); //Change the value of the selected Go Transform

		//Editor save level
		bool saveProject();


		bool startRuntime();


		void loadAssets(AssetManager& manager);


		//Getter
		std::string GetSessionName() const { return sessionName; }
		std::string GetSessionNameStatus() const { return sessionNameStatus; }
		bool GetLoadProject() const { return LoadProjectDial; }
		std::string GetProjectPath() const {return projectPath;}
		bool GetLoadReady() const { return LoadReady; }
		//Setter
		void SetSessionName(std::string session) { sessionName = session; }
		void SetSessionNameStatus(std::string txt) { sessionNameStatus = txt; }
		void SetLoadSession(bool activated) { LoadProjectDial = activated; }
		void SetProjectPath(std::string path) { projectPath = path; }
		void SetLoadReady(bool ready) { LoadReady = ready; }
	};
}