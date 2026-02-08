#pragma once
#include "../Core/Headers/Time_Manager/TimeManager.hpp"
#include "../Core/Headers/Input_Manager/InputManager.hpp"
#include "../Core/Headers/Logger/Logger.hpp"
#include "../Core/Headers/Window/Window.hpp"



namespace Engine
{

    class CoreEngine {
    private:
		// Besoin d'ajouter les autres syst�mes comme le rendu, la gestion des sc�nes, etc.

        InputManager inputManager;
        TimeManager timeManager;
		LoggerManager loggerManager;
		WindowOpener windowOpener;

        //.... assetManager;
        //.... entityManager
        //.... SceneManager
        bool running = false;
    public:

		CoreEngine() = default;

		void init();        // initialisation du moteur
        void run();       // boucle principale
		void shutdown();    // shutdown du moteur
    };
}