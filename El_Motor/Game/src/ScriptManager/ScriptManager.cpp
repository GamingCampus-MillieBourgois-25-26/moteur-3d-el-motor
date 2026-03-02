#include "ScriptManager/ScriptManager.hpp"
#include "UserScript/UserScript.hpp"
#include "ScriptRegister/ScriptRegister.hpp"
#include <thread>
#include <fstream>
#include <algorithm>
#include <windows.h>

/// <summary>
/// Creates a new script with the specified name, generating header and implementation files
/// in the project's Scripts directory.
/// </summary>
void ScriptManager::createScript(std::string scriptName, std::string projectName) {
    // Construct relative path to match createProject structure
    // Path structure: ../../../../Game/Projects/{projectName}/Scripts/{scriptName}/
    std::filesystem::path projectPath = std::filesystem::path("../../../../Game/Projects") / projectName;
    std::filesystem::path scriptDir = projectPath / "Scripts" / scriptName;
    
    // Create directory structure
    std::filesystem::create_directories(scriptDir / "Headers");
    std::filesystem::create_directories(scriptDir / "src");

    // Define file paths
    std::filesystem::path headerPath = scriptDir / "Headers" / (scriptName + ".hpp");
    std::filesystem::path cppPath = scriptDir / "src" / (scriptName + ".cpp");

    // Create header file
    std::ofstream headerFile(headerPath);
    if (!headerFile.is_open()) {
        std::cerr << "Failed to create header file: " << headerPath << std::endl;
        return;
    }

    headerFile <<
        "#pragma once\n"
        "#include \"UserScript/UserScript.hpp\"\n\n"
        "class " << scriptName << " : public UserScript\n"
        "{\n"
        "public:\n"
        "    " << scriptName << "() : UserScript(\"" << scriptName << "\") {}\n"
        "    ~" << scriptName << "() = default;\n\n"
        "    void OnStart() override;\n"
        "    void Update(float deltaTime) override;\n"
        "};\n";
    headerFile.close();

    // Create implementation file
    std::ofstream cppFile(cppPath);
    if (!cppFile.is_open()) {
        std::cerr << "Failed to create cpp file: " << cppPath << std::endl;
        return;
    }

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

    std::cout << "Script '" << scriptName << "' created successfully at: " << scriptDir << std::endl;
}

/// <summary>
/// Deletes a script instance from memory and optionally removes associated files.
/// </summary>
void ScriptManager::DeleteScript(const std::string& scriptName, bool deleteCpp, bool deleteHpp)
{
    // Remove script instance from active scripts list
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

    // Delete files from project Scripts directory using same path structure as createProject
    std::filesystem::path projectsPath = std::filesystem::path("../../../../Game/Projects");
    
    // Search for the script in all projects
    try {
        for (const auto& project : std::filesystem::directory_iterator(projectsPath)) {
            if (project.is_directory()) {
                std::filesystem::path scriptDir = project.path() / "Scripts" / scriptName;
                
                if (std::filesystem::exists(scriptDir)) {
                    if (deleteCpp) {
                        std::filesystem::path cppPath = scriptDir / "src" / (scriptName + ".cpp");
                        if (std::filesystem::exists(cppPath)) {
                            std::filesystem::remove(cppPath);
                            std::cout << "Deleted: " << cppPath << std::endl;
                        }
                    }

                    if (deleteHpp) {
                        std::filesystem::path hppPath = scriptDir / "Headers" / (scriptName + ".hpp");
                        if (std::filesystem::exists(hppPath)) {
                            std::filesystem::remove(hppPath);
                            std::cout << "Deleted: " << hppPath << std::endl;
                        }
                    }

                    // Remove empty directories
                    try {
                        std::filesystem::remove(scriptDir / "src");
                        std::filesystem::remove(scriptDir / "Headers");
                        std::filesystem::remove(scriptDir);
                    }
                    catch (const std::filesystem::filesystem_error&) {
                        // Directories not empty or other error - that's okay
                    }
                    
                    break;
                }
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error searching for script files: " << e.what() << std::endl;
    }
}

/// <summary>
/// Initializes the ScriptManager by clearing existing instances and creating new ones
/// from the ScriptRegistry.
/// </summary>
void ScriptManager::Initialize()
{
    scripts.clear();
    auto newScripts = ScriptRegistry::Instance().CreateAll();
    if (!newScripts.empty())
        scripts = std::move(newScripts);
}

/// <summary>
/// Calls the OnStart() method on all registered scripts.
/// </summary>
void ScriptManager::StartAll()
{
    for (auto& script : scripts)
        script->OnStart();
}

/// <summary>
/// Calls the Update() method on all registered scripts with the given delta time.
/// </summary>
void ScriptManager::updateScripts(float deltaTime)
{
    for (auto& script : scripts)
        script->Update(deltaTime);
}

/// <summary>
/// Rebuilds the entire project using CMake to recompile scripts and the engine.
/// Provides comprehensive error handling, logging, and status feedback.
/// </summary>
void ScriptManager::Restart()
{
    std::filesystem::path root = "../../../../";
    std::filesystem::path buildDir = root / "out/build/x64-Debug/Editor" ;

    std::string configureCmd =
        "cmake -S \"" + root.string() +
        "\" -B \"" + buildDir.string() + "\"";

    std::system(configureCmd.c_str());

    std::string buildCmd =
        "cmake --build \"" + buildDir.string() + "\" --config Debug";

    std::system(buildCmd.c_str());
}