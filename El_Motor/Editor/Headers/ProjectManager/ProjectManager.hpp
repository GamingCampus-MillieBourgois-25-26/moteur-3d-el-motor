#pragma once
#include <string>
#include <filesystem>
#include "Scene/Scene.hpp"
#include "Entity/GameObject.hpp"
#include <vector>

namespace Editor {

	/// <summary>
	/// Class responsible for managing editor projects.
	/// Handles project creation, loading, saving, and
	/// scene serialization within a project directory.
	/// </summary>
	class ProjectManager {

	private:

		/// Name of the currently loaded project
		std::string loadedProjectName;

	protected:

		/// Path to the currently opened project
		std::filesystem::path currentProjectPath;

		/// <summary>
		/// Loads a scene from a file path and populates the provided scene object.
		/// </summary>
		/// <param name="path">Path to the scene file</param>
		/// <param name="scene">Scene instance to load data into</param>
		void loadScene(const std::filesystem::path& path, std::shared_ptr<Engine::Scene>& scene);

	public:

		/// <summary>
		/// Returns the singleton instance of the ProjectManager.
		/// </summary>
		/// <returns>Reference to the ProjectManager instance</returns>
		static ProjectManager& Get();

		/// <summary>
		/// Destructor
		/// </summary>
		~ProjectManager();

		// =========================
		// Project Creation
		// =========================

		/// <summary>
		/// Creates a new project with the specified name
		/// and initializes its scene.
		/// </summary>
		/// <param name="name">Name of the project</param>
		/// <param name="scene">Scene associated with the new project</param>
		void createProject(const std::string& name, std::shared_ptr<Engine::Scene>& scene);

		// =========================
		// Project Loading
		// =========================

		/// <summary>
		/// Loads a project and all resources contained within it.
		/// </summary>
		/// <param name="path">Path to the project directory</param>
		/// <param name="scene">Scene that will receive the loaded data</param>
		void loadProject(const std::filesystem::path& path, std::shared_ptr<Engine::Scene>& scene);

		// =========================
		// Last Project Handling
		// =========================

		/// <summary>
		/// Stores the name of the last opened project.
		/// </summary>
		/// <param name="name">Project name</param>
		void SetLastProject(const std::string& name);

		/// <summary>
		/// Clears the stored last project information.
		/// </summary>
		void clearLastProject();

		// =========================
		// Project Saving
		// =========================

		/// <summary>
		/// Saves the current project and all associated scenes.
		/// </summary>
		/// <param name="scenes">Scene to save</param>
		void saveProject(std::shared_ptr<Engine::Scene>& scenes);

		/// <summary>
		/// Saves a specific scene to a file.
		/// </summary>
		/// <param name="scene">Scene to serialize</param>
		/// <param name="scenePath">Destination file path</param>
		void saveScene(const Engine::Scene& scene, const std::filesystem::path& scenePath);

		// =========================
		// Setters
		// =========================

		/// <summary>
		/// Sets the current project path.
		/// </summary>
		/// <param name="path">Project directory path</param>
		void SetProjectPath(const std::filesystem::path& path) { currentProjectPath = path; }

		/// <summary>
		/// Sets the name of the loaded project.
		/// </summary>
		/// <param name="name">Project name</param>
		void SetLoadedProjectName(const std::string& name) { loadedProjectName = name; }

		// =========================
		// Getters
		// =========================

		/// <summary>
		/// Returns the current project path.
		/// </summary>
		/// <returns>Path to the loaded project</returns>
		const std::filesystem::path& GetProjectPath() const;

		/// <summary>
		/// Returns the name of the currently loaded project.
		/// </summary>
		/// <returns>Project name</returns>
		std::string GetLoadedProjectName() const { return loadedProjectName; }

	};
}