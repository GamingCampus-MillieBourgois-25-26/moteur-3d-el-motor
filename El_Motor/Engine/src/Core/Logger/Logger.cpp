#include "Core/Logger/Logger.hpp"

#include <iostream>
#include <ostream>
#include <string>
#include <filesystem>
#include <fstream>

Engine::LoggerManager& Engine::LoggerManager::Get()
{
    static LoggerManager instance; // unique instance
    return instance;
}

void Engine::LoggerManager::LogInitialize()
{
    std::cout << "Logger initialized." << std::endl;
    LogInfo("Logger initialized.");
}

void Engine::LoggerManager::LogShutdown()
{
    std::cout << "Logger shutdown." << std::endl;
    LogInfo("Logger shutdown.");
}

// Fonctions de log sp�cifiques pour chaque type de message, qui appellent la fonction Log avec le type appropri�.
void Engine::LoggerManager::LogError(const std::string& message)
{
    Log(message, LogType::Error);
}

void Engine::LoggerManager::LogWarning(const std::string& message)
{
    Log(message, LogType::Warning);
}

void Engine::LoggerManager::LogInfo(const std::string& message)
{
    Log(message, LogType::Info);
}

// Logique de log simple qui affiche les messages dans la console selon leur type.
void Engine::LoggerManager::Log(const std::string& message, LogType type)
{
    switch (type)
    {
    case LogType::Error:
        std::cerr << "[ERROR] " << message << std::endl;
        LogToFile("[ERROR] " + message);
        break;
    case LogType::Warning:
        std::cerr << "[WARNING] " << message << std::endl;
        LogToFile("[WARNING] " + message);
        break;
    case LogType::Info:
        std::cout << "[INFO] " << message << std::endl;
        LogToFile("[INFO] " + message);
        break;
    default:
        std::cout << "[UNKNOWN] " << message << std::endl;
        LogToFile("[UNKNOWN] " + message);
        break;
    }
}

// Fonction qui �crit les messages de log dans un fichier. Elle v�rifie d'abord si le dossier existe et le cr�e si n�cessaire, puis ouvre le fichier et �crit le message.
void Engine::LoggerManager::LogToFile(const std::string& message)
{
    std::filesystem::path logPath(logFilePath);

    if (!std::filesystem::exists(logPath.parent_path()))
    {
        std::filesystem::create_directories(logPath.parent_path());
    }

    std::ofstream file(logFilePath, std::ios::app);
    if (file)
    {
        file << message << std::endl;
    }
    else
    {
        std::cerr << "[LOGGER ERROR] Unable to open log file: " << logFilePath << std::endl;
    }
}
