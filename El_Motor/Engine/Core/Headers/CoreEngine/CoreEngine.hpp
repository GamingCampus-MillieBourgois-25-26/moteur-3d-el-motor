#pragma once
#include "../Core/Headers/Time_Manager/TimeManager.hpp"
#include "../Core/Headers/Input_Manager/InputManager.hpp"
#include "../Core/Headers/Logger/Logger.hpp"
#include "../Core/Headers/Application/App.hpp"
//#include "../Core/Headers/Window/Window.hpp"



namespace Engine
{

    class CoreEngine {
    private:
		// Besoin d'ajouter les autres syst�mes comme le rendu, la gestion des sc�nes, etc.

        InputManager inputManager;
        TimeManager timeManager;
		LoggerManager loggerManager;
		Application application;


        //.... assetManager;
        //.... entityManager
        //.... SceneManager

        bool running = false;
    public:

		CoreEngine() = default;

		void init();         // initialisation du moteur
        void run();         // boucle principale
		void shutdown();   // shutdown du moteur
		bool isRunning() const { return running; } // vérifie si le moteur est en cours d'exécution
		bool shouldClose() const { return application.windowOpener->getMyWindow(); } // vérifie si la fenêtre doit se fermer

		// Getters pour les différents systèmes du moteur
		InputManager& getInputManager() { return inputManager; }
		TimeManager& getTimeManager() { return timeManager; }
		LoggerManager& getLoggerManager() { return loggerManager; }
		WindowOpener& getWindowOpener() { return application.getWindowOpener(); }

    };
}