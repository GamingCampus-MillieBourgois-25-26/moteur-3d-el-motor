#pragma once
#include <string>
#include <iostream>
#include <fstream>




namespace Engine
{

	//Types de log
	enum class LogType
	{
		Error,
		Warning,
		Info
	};

	class LoggerManager
	{
	protected:

	public:
		//Constructeur et destructeur
		LoggerManager() {};
		~LoggerManager() {};

		//Fonctions de log
		void LogInitialize();
		void LogShutdown();

		void Log(const std::string& message, LogType type = LogType::Info);

		void LogError(const std::string& message);
		void LogWarning(const std::string& message);
		void LogInfo(const std::string& message);

		void LogToFile(const std::string& message, const std::string& filename);

	private:


	};
}