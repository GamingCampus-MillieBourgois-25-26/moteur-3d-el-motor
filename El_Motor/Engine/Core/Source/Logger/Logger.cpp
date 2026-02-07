#include "../Core/Headers/Logger/Logger.hpp"

void Engine::LoggerManager::LogInitialize()
{
	std::cout << "Logger initialized." << std::endl;
}
void Engine::LoggerManager::LogShutdown()
{
	std::cout << "Logger shutdown." << std::endl;
}

// Logique de log simple qui affiche les messages dans la console selon leur type.
void Engine::LoggerManager::Log(const std::string& message, LogType type)
{
	switch (type)
	{
	case LogType::Error:
		std::cerr << "[ERROR] " << message << std::endl;
		break;
	case LogType::Warning:
		std::cerr << "[WARNING] " << message << std::endl;
		break;
	case LogType::Info:
		std::cout << "[INFO] " << message << std::endl;
		break;
	default:
		std::cout << "[UNKNOWN] " << message << std::endl;
		break;
	}
}



// Fonctions de log spécifiques pour chaque type de message, qui appellent la fonction Log avec le type approprié.
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




void Engine::LoggerManager::LogToFile(const std::string& message, const std::string& filename)
{
	std::ofstream file(filename, std::ios::app);
	if (file.is_open())
	{
		file << message << std::endl;
		file.close();
	}
	else
	{
		std::cerr << "[ERROR] Unable to open log file: " << filename << std::endl;
	}
}