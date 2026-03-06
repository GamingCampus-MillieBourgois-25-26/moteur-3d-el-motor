#pragma once
#include <string>
#include <filesystem>
#include "Scene/Scene.hpp"
#include "Entity/GameObject.hpp"
#include <vector>

namespace Editor {

	class ProjectManager {

	private:
		std::string loadedProjectName;

	protected:
		std::filesystem::path currentProjectPath;
		void loadScene(const std::filesystem::path& path, std::shared_ptr<Engine::Scene>& scene);


	public:

		static ProjectManager& Get();
		~ProjectManager();

		//create project
		void createProject(const std::string& name, std::shared_ptr<Engine::Scene>& scene);

		//Load project and everything contained in the project
		void loadProject(const std::filesystem::path& path, std::shared_ptr<Engine::Scene>& scene);
		


		//
		void SetLastProject(const std::string& name);
		void clearLastProject();


		//Save Project
		void saveProject(std::shared_ptr<Engine::Scene>& scenes);
		void saveScene(const Engine::Scene& scene, const std::filesystem::path& scenePath);

		//Setter
		void SetProjectPath(const std::filesystem::path& path) {currentProjectPath = path;}
		void SetLoadedProjectName(const std::string& name) { loadedProjectName = name; }


		//Getter
		const std::filesystem::path& GetProjectPath() const;
		std::string GetLoadedProjectName() const { return loadedProjectName; }






	};
}