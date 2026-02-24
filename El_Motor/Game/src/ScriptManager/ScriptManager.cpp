#include "ScriptManager/ScriptManager.hpp"
#include "UserScript/UserScript.hpp"
#include <fstream>

void ScriptManager::createScript(std::string scriptName) {
    std::ofstream headerFile(scriptName + ".hpp");
    headerFile << "#pragma once" << std::endl; 
    headerFile << "#include \"Script.hpp\"" << std::endl << std::endl;
    headerFile << "class " << scriptName << " : public Script {" << std::endl;
    headerFile << "public:" << std::endl;
    headerFile << "    void OnStart() override;" << std::endl;
    headerFile << "    void Update() override;" << std::endl;
    headerFile << "};" << std::endl;

    // Crée le fichier .cpp
    std::ofstream cppFile(scriptName + ".cpp");
    cppFile << "#include \"" << scriptName << ".hpp\"" << std::endl << std::endl;
    cppFile << "void " << scriptName << "::OnStart() {" << std::endl;
    cppFile << "    // Implémentation de OnStart" << std::endl;
    cppFile << "}" << std::endl << std::endl;
    cppFile << "void " << scriptName << "::Update() {" << std::endl;
    cppFile << "    // Implémentation de Update" << std::endl;
    cppFile << "}" << std::endl;
}

void ScriptManager::updateScripts(float deltatime) {
	for (auto& script : scripts) {
		(*script)->Update(deltatime);
	}
}

void ScriptManager::destroyScript(std::string scriptName) {
	scripts.erase(std::remove_if(scripts.begin(), scripts.end(),
		[scriptName](const std::unique_ptr<UserScript*>& script) {
			return (*script)->GetName() == scriptName;
		}), scripts.end());
}