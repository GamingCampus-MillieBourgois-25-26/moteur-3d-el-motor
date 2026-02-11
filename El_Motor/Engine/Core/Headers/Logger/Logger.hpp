#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>



namespace Engine
{

	//Types de log

	class LoggerManager
	{
	protected:
		
	public:

		static LoggerManager& Get();

		//Constructeur et destructeur
		LoggerManager() = default;
		~LoggerManager() = default;
		LoggerManager(const LoggerManager&) = delete; // Empêche la copie de l'instance
		LoggerManager& operator=(const LoggerManager&) = delete; // Empêche l'assignation de l'instance

		//Fonctions d'init et de shutdown du logger
		void LogInitialize();
		void LogShutdown();

		
		// Fonctions de log spécifiques pour chaque type de message
		void LogError(const std::string& message);
		void LogWarning(const std::string& message);
		void LogInfo(const std::string& message);

		

	private:

	enum class LogType{Error,Warning,Info};

	std::string logFilePath = "..\\UserLog.txt"; // Chemin par défaut pour les logs

	void Log(const std::string& message, LogType type = LogType::Info);
	void LogToFile(const std::string& message);
	};
}