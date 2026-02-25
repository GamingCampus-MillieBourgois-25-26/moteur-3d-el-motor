#include "ScriptManager/ScriptManager.hpp"
#include "UserScript/UserScript.hpp"
#include <fstream>
#include <filesystem>

void ScriptManager::createScript(std::string scriptName) {
    std::ofstream headerFile(scriptName + ".hpp");
    headerFile << "#pragma once" << std::endl; 
    headerFile << "#include \"UserScript.hpp\"" << std::endl << std::endl;
    headerFile << "class " << scriptName << " : public UserScript {" << std::endl;
    headerFile << "public:" << std::endl;
    headerFile << "    void OnStart() override;" << std::endl;
    headerFile << "    void Update() override;" << std::endl;
    headerFile << "};" << std::endl;

    // Crée le fichier .cpp
    std::ofstream cppFile(scriptName + ".cpp");
    cppFile << "#include \"" << scriptName << ".hpp\"" << std::endl << std::endl;
    cppFile << "//This funtion is called when the script is first loaded, and is used to initialize any variables or set up any necessary components for the script to function properly. It is typically called once at the beginning of the script's lifecycle." << std::endl;
    cppFile << "void " << scriptName << "::OnStart() {" << std::endl;
    cppFile << "    // Implémentation de OnStart" << std::endl;
    cppFile << "}" << std::endl << std::endl;
    cppFile << "//This function is called every frame, and is used to update the script's behavior or perform any necessary actions based on the current state of the game. It is typically called repeatedly throughout the script's lifecycle, allowing for dynamic and responsive behavior." << std::endl;
    cppFile << "void " << scriptName << "::Update() {" << std::endl;
    cppFile << "    // Implémentation de Update" << std::endl;
    cppFile << "}" << std::endl;
    files.emplace_back(cppFile);
}

void ScriptManager::updateScripts(float deltatime) {
    for (auto& file : files) {
        
    }

}

void ScriptManager::destroyScript(std::string scriptName) {
    for (auto& file : files) {

    }
}