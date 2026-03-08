#pragma once
#include "CoreEngine/CoreEngine.hpp"
#include "Application/App.hpp"

namespace Editor
{
	/// <summary>
	/// Classe responsable de la gestion du cœur de l'éditeur.
	/// Coordonne l'initialisation, l'exécution et l'arrêt de l'éditeur,
	/// ainsi que la gestion des entrées utilisateur et du moteur graphique.
	/// </summary>
	class EditorCore
	{
	private:
		/// Moteur graphique principal de l'éditeur
		Engine::CoreEngine coreEngine;
		
		/// Position X de la souris dans l'espace de l'éditeur
		double x = 0.0;
		
		/// Position Y de la souris dans l'espace de l'éditeur
		double y = 0.0;

	protected:
		// Espace réservé pour les membres protégés

	public:
		/// <summary>
		/// Constructeur par défaut
		/// </summary>
		EditorCore() {}
		
		/// <summary>
		/// Destructeur
		/// </summary>
		~EditorCore() {}

		/// <summary>
		/// Initialise l'éditeur et ses composants.
		/// </summary>
		/// <param name="app">Référence à l'application principale</param>
		void editorInit(Engine::Application& app);
		
		/// <summary>
		/// Boucle principale d'exécution de l'éditeur.
		/// </summary>
		/// <param name="app">Référence à l'application principale</param>
		void editorRun(Engine::Application& app);
		
		/// <summary>
		/// Arrête l'éditeur et libère les ressources.
		/// </summary>
		void editorShutdown();
		
		/// <summary>
		/// Lance le mode d'exécution du jeu/projet.
		/// </summary>
		void startRuntime();

		/// <summary>
		/// Met à jour les entrées utilisateur (clavier, souris, etc.).
		/// </summary>
		/// <param name="app">Référence à l'application principale</param>
		void InputUpdate(Engine::Application& app);
		
		/// <summary>
		/// Retourne la position X actuelle de la souris dans l'éditeur.
		/// </summary>
		/// <returns>Coordonnée X de la souris</returns>
		double getMouseEditorX() const { return x; }
		
		/// <summary>
		/// Retourne la position Y actuelle de la souris dans l'éditeur.
		/// </summary>
		/// <returns>Coordonnée Y de la souris</returns>
		double getMouseEditorY() const { return y; }

		/// <summary>
		/// Accède au moteur graphique principal.
		/// </summary>
		/// <returns>Référence non-const au moteur graphique</returns>
		Engine::CoreEngine& GetEngine() { return coreEngine; }
	};
}