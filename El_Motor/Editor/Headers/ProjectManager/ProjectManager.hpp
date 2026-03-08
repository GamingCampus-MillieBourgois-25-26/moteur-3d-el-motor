#pragma once
#include <string>
#include <filesystem>
#include "Scene/Scene.hpp"
#include "Entity/GameObject.hpp"
#include <vector>

namespace Editor {

    /**
     * @brief Class responsible for managing editor projects.
     *
     * Handles project creation, loading, saving, and
     * scene serialization within a project directory.
     */
    class ProjectManager {

    private:
        /// @brief Name of the currently loaded project
        std::string loadedProjectName;

    protected:
        /// @brief Path to the currently opened project
        std::filesystem::path currentProjectPath;

        /**
         * @brief Loads a scene from a file path and populates the provided scene object.
         *
         * @param path Path to the scene file
         * @param scene Scene instance to load data into
         */
        void loadScene(const std::filesystem::path& path, std::shared_ptr<Engine::Scene>& scene);

    public:
        /**
         * @brief Returns the singleton instance of the ProjectManager.
         *
         * @return Reference to the ProjectManager instance
         */
        static ProjectManager& Get();

        /**
         * @brief Destructor
         */
        ~ProjectManager();

        // =========================
        // Project Creation
        // =========================

        /**
         * @brief Creates a new project with the specified name
         *        and initializes its scene.
         *
         * @param name Name of the project
         * @param scene Scene associated with the new project
         */
        void createProject(const std::string& name, std::shared_ptr<Engine::Scene>& scene);

        // =========================
        // Project Loading
        // =========================

        /**
         * @brief Loads a project and all resources contained within it.
         *
         * @param path Path to the project directory
         * @param scene Scene that will receive the loaded data
         */
        void loadProject(const std::filesystem::path& path, std::shared_ptr<Engine::Scene>& scene);

        // =========================
        // Last Project Handling
        // =========================

        /**
         * @brief Stores the name of the last opened project.
         *
         * @param name Project name
         */
        void SetLastProject(const std::string& name);

        /**
         * @brief Clears the stored last project information.
         */
        void clearLastProject();

        // =========================
        // Project Saving
        // =========================

        /**
         * @brief Saves the current project and all associated scenes.
         *
         * @param scenes Scene to save
         */
        void saveProject(std::shared_ptr<Engine::Scene>& scenes);

        /**
         * @brief Saves a specific scene to a file.
         *
         * @param scene Scene to serialize
         * @param scenePath Destination file path
         */
        void saveScene(const Engine::Scene& scene, const std::filesystem::path& scenePath);

        // =========================
        // Setters
        // =========================

        /**
         * @brief Sets the current project path.
         *
         * @param path Project directory path
         */
        void SetProjectPath(const std::filesystem::path& path) { currentProjectPath = path; }

        /**
         * @brief Sets the name of the loaded project.
         *
         * @param name Project name
         */
        void SetLoadedProjectName(const std::string& name) { loadedProjectName = name; }

        // =========================
        // Getters
        // =========================

        /**
         * @brief Returns the current project path.
         *
         * @return Path to the loaded project
         */
        const std::filesystem::path& GetProjectPath() const;

        /**
         * @brief Returns the name of the currently loaded project.
         *
         * @return Project name
         */
        std::string GetLoadedProjectName() const { return loadedProjectName; }

    };
}