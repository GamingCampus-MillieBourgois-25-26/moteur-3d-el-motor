#pragma once
#include <vector>


namespace Engine {

	class ScriptManager {

	private:

		std::vector<ScriptManager> scripts;

	public:

		void CreateScript();
		void DeleteScript();
		void updateScript();
		


		std::vector<ScriptManager> GetUserScript(){ return scripts; }






	};




}