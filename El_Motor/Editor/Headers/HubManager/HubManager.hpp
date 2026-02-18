#pragma once
#include <iostream>
#include "EditCore/EditCore.hpp"
#include "ImGuiLayer/ImGuiLayer.hpp"
#include "Application/App.hpp"
#include "GuiToolBarPanel/Buttons.hpp"

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
		std::string sessionName = "Null";
		EditorState editorState = Hub;
		Engine::LoggerManager logger;

	
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
		std::string GetSessionName() const { return sessionName; }
		EditorState GetEditorState() const { return editorState; }
		//Setters
		void SetSessionName(std::string name) { sessionName = name; }
		void SetEditorState(EditorState state) { editorState = state; }
	};

}