#include "ScriptManager/ScriptManager.hpp"
#include "UserScript/UserScript.hpp"
#include "ScriptRegister/ScriptRegister.hpp"
#include <thread>
#include <fstream>
#include <algorithm>
#include <windows.h>

void ScriptManager::createScript(std::string scriptName, std::string projectName) {
    std::filesystem::path project = "Projects/" + projectName;
    std::filesystem::path directory = project/("Scripts/" + scriptName);
    std::filesystem::create_directories(directory);

    std::filesystem::path headerPath = directory / ("Headers/" + scriptName + ".hpp");
    std::filesystem::path cppPath = directory / ("src/" + scriptName + ".cpp");
    std::filesystem::create_directories(headerPath.parent_path());
    std::filesystem::create_directories(cppPath.parent_path());


    std::ofstream headerFile(headerPath);
    headerFile <<
        "#pragma once\n"
        "#include \"UserScript/UserScript.hpp\"\n\n"
        "class " << scriptName << " : public UserScript\n"
        "{\n"
        "public:\n"
        "    " << scriptName << "() : UserScript(\"" << scriptName << "\") {}\n\n"
        "    void OnStart() override;\n"
        "    void Update(float deltaTime) override;\n"
        "};\n";
    headerFile.close();


    std::ofstream cppFile(cppPath);
    cppFile <<
        "#include \"../Headers/" << scriptName << ".hpp\"\n"
        "#include \"MacroAutoRegister/AutoRegister.hpp\"\n"
        "#include <iostream>\n\n"

        "void " << scriptName << "::OnStart()\n"
        "{\n"
        "    std::cout << \"" << scriptName << " Started\" << std::endl;\n"
        "}\n\n"

        "void " << scriptName << "::Update(float deltaTime)\n"
        "{\n"
        "}\n\n"

        "REGISTER_SCRIPT(" << scriptName << ");\n";
    cppFile.close();
}



void ScriptManager::DeleteScript(const std::string& scriptName, bool deleteCpp, bool deleteHpp)
{
    auto it = std::remove_if(scripts.begin(), scripts.end(),
        [&](const std::unique_ptr<UserScript>& s) {
            return s->GetName() == scriptName;
        });

    if (it != scripts.end()) {
        scripts.erase(it, scripts.end());
        std::cout << "Instance of script '" << scriptName << "' deleted from memory." << std::endl;
    }
    else {
        std::cout << "No instance of script '" << scriptName << "' found in memory." << std::endl;
    }

    // Suppression fichiers
    std::filesystem::path directory = "Scripts/" + scriptName;

    if (deleteCpp) {
        std::filesystem::path cppPath = directory / ("src/" + scriptName + ".cpp");
        if (std::filesystem::exists(cppPath)) {
            std::filesystem::remove(cppPath);
            std::cout << "Deleted " << cppPath << std::endl;
        }
    }

    if (deleteHpp) {
        std::filesystem::path hppPath = directory / ("Headers/" + scriptName + ".hpp");
        if (std::filesystem::exists(hppPath)) {
            std::filesystem::remove(hppPath);
            std::cout << "Deleted " << hppPath << std::endl;
        }
    }
}


void ScriptManager::Initialize()
{
    scripts.clear();
    auto newScripts = ScriptRegistry::Instance().CreateAll();
    if (!newScripts.empty())
        scripts = std::move(newScripts);
}

void ScriptManager::StartAll()
{
    for (auto& script : scripts)
        script->OnStart();
}

void ScriptManager::updateScripts(float deltaTime)
{
    for (auto& script : scripts)
        script->Update(deltaTime);
}

void ScriptManager::Restart()
{
    std::string projectRoot = "C:/Users/Aracno/Documents/GitHub/moteur-3d-el-motor/El_Motor"; // temporaire pour test

    std::string configureCmd = "cmake -S \"" + projectRoot + "\" -B \"" + projectRoot + "/out/build\"";
    std::system(configureCmd.c_str());

    std::string buildCmd = "cmake --build \"" + projectRoot + "/out/build\" --config Debug";
    std::system(buildCmd.c_str());
}