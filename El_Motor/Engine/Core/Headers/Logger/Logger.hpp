#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace Engine {

    /// <summary>
    /// Singleton class responsible for logging messages to console and file.
    /// Supports Info, Warning, and Error log types.
    /// </summary>
    class LoggerManager {
    public:

        /// <summary>
        /// Returns the singleton instance of the LoggerManager.
        /// </summary>
        static LoggerManager& Get();

        /// <summary>
        /// Default constructor.
        /// </summary>
        LoggerManager() = default;

        /// <summary>
        /// Default destructor.
        /// </summary>
        ~LoggerManager() = default;

        // Prevent copy/assignment
        LoggerManager(const LoggerManager&) = delete;
        LoggerManager& operator=(const LoggerManager&) = delete;

        // =========================
        // Initialization / Shutdown
        // =========================

        /// <summary>
        /// Initializes the logger (e.g., opens log file).
        /// </summary>
        void LogInitialize();

        /// <summary>
        /// Shuts down the logger (e.g., closes log file).
        /// </summary>
        void LogShutdown();

        // =========================
        // Logging functions
        // =========================

        /// <summary>
        /// Logs an error message.
        /// </summary>
        void LogError(const std::string& message);

        /// <summary>
        /// Logs a warning message.
        /// </summary>
        void LogWarning(const std::string& message);

        /// <summary>
        /// Logs an info message.
        /// </summary>
        void LogInfo(const std::string& message);

    private:

        /// <summary>
        /// Internal log type enumeration.
        /// </summary>
        enum class LogType { Error, Warning, Info };

        /// <summary>
        /// Default path for the log file.
        /// </summary>
        std::string logFilePath = "..\\UserLog.txt";

        /// <summary>
        /// Internal function to log a message with a given type.
        /// </summary>
        void Log(const std::string& message, LogType type = LogType::Info);

        /// <summary>
        /// Writes a message to the log file.
        /// </summary>
        void LogToFile(const std::string& message);
    };
}