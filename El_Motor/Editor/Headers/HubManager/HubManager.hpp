#pragma once
#include <iostream>
#include "EditCore/EditCore.hpp"
#include "ImGuiLayer/ImGuiLayer.hpp"
#include "Application/App.hpp"
#include "GuiToolBarPanel/Buttons.hpp"
#include <vector>

namespace Editor
{
	class HubManager
	{
	protected:
		//Engine::Application app;
		enum EditorState
		{
			Hub,
			Editor
		};
		Engine::Application app;
	private:


		//Variables
		Buttons buttons;
		EditorCore coreEditor;
		GuiLayer guiLayer;
		EditorState editorState = Hub;
		Engine::LoggerManager logger;
		//std::vector<Engine::Scene*> Levels;
		//std::shared_ptr<Engine::Scene>* currentLevel = &coreEditor.GetEngine().getScene();
	
	public:

		HubManager();
		~HubManager();


		//Functions
		void Init();
		void HubRun();
		void CreateProject();
		void LoadProject();

		void DrawHubUI();
		void DrawEditorUI();


		//Getters
		EditorState& GetEditorState()  { return editorState; }
		//std::vector<Engine::Scene*>& GetLevels() { return Levels; }


		//setter
		void SetEditorState(EditorState state) { editorState = state; }

		//void createNewLevel();
	};

}