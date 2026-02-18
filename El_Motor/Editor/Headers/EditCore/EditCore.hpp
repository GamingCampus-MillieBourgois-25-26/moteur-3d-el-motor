#pragma once
#include "CoreEngine/CoreEngine.hpp"
#include "Application/App.hpp"
namespace Editor
{
	class EditorCore
	{


	private:
	
		Engine::CoreEngine coreEngine;
		double x = 0.0;
		double y = 0.0;


	protected:

	public:
		EditorCore() {}
		~EditorCore() {}

		void editorInit();
		void editorRun(Engine::Application& app);
		void editorShutdown();
		void startRuntime();


		void InputUpdate(Engine::Application& app);
		double getMouseEditorX() const { return x; }
		double getMouseEditorY() const { return y; }

		Engine::CoreEngine&  GetEngine() { return coreEngine; }


	};
}