#pragma once
#include "../Core/Headers/Time_Manager/TimeManager.hpp"
#include "../Core/Headers/Input_Manager/InputManager.hpp"
#include "../Core/Headers/Window/Window.hpp"



namespace Engine
{

    class CoreEngine {
    private:
		// Besoin d'ajouter les autres systèmes comme le rendu, la gestion des scènes, etc.

        InputManager inputManager;
        TimeManager timeManager;
		WindowOpener windowOpener;

        //.... assetManager;
        //.... entityManager
        //.... SceneManager
        bool running = false;
    public:
		void init();        // initialisation du moteur
        void run();       // boucle principale
		void shutdown();    // arrêt du moteur
        void render();
    };
}