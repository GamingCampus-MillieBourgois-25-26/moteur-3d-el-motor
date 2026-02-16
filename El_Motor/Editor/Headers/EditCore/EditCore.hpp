#pragma once
#include "CoreEngine/CoreEngine.hpp"

namespace Editor
{
	class EditorCore
	{


	private:
	


	protected:
		Engine::CoreEngine coreEngine;

	public:
		EditorCore() {}
		~EditorCore() {}

		void editorInit();
		void editorRun();
		void editorShutdown();
		void DrawUi();


		Engine::CoreEngine&  GetEngine() { return coreEngine; }


	};
}