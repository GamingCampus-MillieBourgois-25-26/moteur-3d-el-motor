#pragma once

#include "Time_Manager/TimeManager.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Input_Manager/InputManager.hpp"
#include "Logger/Logger.hpp"
#include "Application/App.hpp"
#include "Scene/Scene.hpp"
#include "Camera/EditorCamera.hpp"

namespace Engine
{

    class CoreEngine {
    private:
		// Besoin d'ajouter les autres systemes comme le rendu, la gestion des scenes, etc.
        InputManager inputManager;
        TimeManager timeManager;
		LoggerManager loggerManager;
		AssetManager assetManager;
		std::shared_ptr<Scene> defaultScene;
		EditorCamera camera;
        //.... assetManager;

        bool running = false;
		float dt = 0.0f;

    public:

		CoreEngine() = default;

		void init();         // initialisation du moteur
        void run();         // boucle principale
		void shutdown();   // shutdown du moteur
		bool isRunning() const { return running; } // vérifie si le moteur est en cours d'exécution
		

		// Getters pour les différents systèmes du moteur
		InputManager& getInputManager() { return inputManager; }
		TimeManager& getTimeManager() { return timeManager; }
		LoggerManager& getLoggerManager() { return loggerManager; }
		/*WindowOpener& getWindowOpener() { return application.getWindowOpener(); }
		Application& getApplication() { return application; }*/
		AssetManager& getAssetManager() { return assetManager; }
		std::shared_ptr<Scene>& getScene() { return defaultScene; }
		EditorCamera& getCamera() { return camera; }
		float getDeltaTime() const { return dt; }


		void SetScene(std::shared_ptr<Scene> scene) { defaultScene = scene; }
		void SetDeltaTime(float delta) { dt = delta; }

    };
}