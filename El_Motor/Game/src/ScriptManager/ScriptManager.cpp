#include "ScriptManager/ScriptManager.hpp"
#include "UserScript/UserScript.hpp"
#include <fstream>


void ScriptManager::createScript(std::string scriptName, std::filesystem::path& directory) {

    std::filesystem::create_directories(directory);

    std::filesystem::path headerPath = directory / (scriptName + ".hpp");
    std::filesystem::path cppPath = directory / (scriptName + ".cpp");


    std::ofstream headerFile(headerPath);
    headerFile << "#pragma once" << std::endl; 
    headerFile << "#include \"UserScript.hpp\"" << std::endl << std::endl;
    headerFile << "class " << scriptName << " : public UserScript {" << std::endl;
    headerFile << "public:" << std::endl;
    headerFile << "    void OnStart() override;" << std::endl;
    headerFile << "    void Update() override;" << std::endl;
    headerFile << "};" << std::endl;
	headerFile.close();


    // Crée le fichier .cpp
    std::ofstream cppFile(cppPath);
    cppFile << "#include \"" << scriptName << ".hpp\"" << std::endl << std::endl;
    cppFile << "//This funtion is called when the script is first loaded, and is used to initialize any variables or set up any necessary components for the script to function properly. It is typically called once at the beginning of the script's lifecycle." << std::endl;
    cppFile << "void " << scriptName << "::OnStart() {" << std::endl;
    cppFile << "    // Implémentation de OnStart" << std::endl;
    cppFile << "}" << std::endl << std::endl;
    cppFile << "//This function is called every frame, and is used to update the script's behavior or perform any necessary actions based on the current state of the game. It is typically called repeatedly throughout the script's lifecycle, allowing for dynamic and responsive behavior." << std::endl;
    cppFile << "void " << scriptName << "::Update() {" << std::endl;
    cppFile << "    // Implémentation de Update" << std::endl;
    cppFile << "}" << std::endl;
	cppFile.close();


}

void ScriptManager::updateScripts(float deltatime) {
    for (auto& script : scripts) 
    {
        script->Update(deltatime);
    }
        
}

void ScriptManager::destroyScript(std::string scriptName) {

}


void ScriptManager::RegisterScript (std::unique_ptr<Script> script)
{
   GetScripts().push_back(std::move(script));
}

void ScriptManager::StartAll()
{
    for (auto& script : scripts)
        script->OnStart();
}