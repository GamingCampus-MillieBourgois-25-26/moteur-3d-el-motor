#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace Engine {

    /**
     * @brief Singleton class responsible for logging messages to console and file.
     *
     * Supports three log levels: Info, Warning, and Error.
     * Messages are written both to the console and to a log file.
     */
    class LoggerManager {
    public:

        /**
         * @brief Returns the singleton instance of LoggerManager.
         * @return Reference to the LoggerManager instance.
         */
        static LoggerManager& Get();

        /**
         * @brief Default constructor.
         */
        LoggerManager() = default;

        /**
         * @brief Default destructor.
         */
        ~LoggerManager() = default;

        // Disable copy and assignment
        LoggerManager(const LoggerManager&) = delete;
        LoggerManager& operator=(const LoggerManager&) = delete;

        // =========================
        // Initialization / Shutdown
        // =========================

        /**
         * @brief Initializes the logger.
         *
         * Opens the log file for writing and prepares internal structures.
         */
        void LogInitialize();

        /**
         * @brief Shuts down the logger.
         *
         * Closes the log file and cleans up resources.
         */
        void LogShutdown();

        // =========================
        // Logging functions
        // =========================

        /**
         * @brief Logs an error message.
         *
         * The message will be written with "ERROR" prefix and sent to both
         * the console and log file.
         * @param message Message to log.
         */
        void LogError(const std::string& message);

        /**
         * @brief Logs a warning message.
         *
         * The message will be written with "WARNING" prefix.
         * @param message Message to log.
         */
        void LogWarning(const std::string& message);

        /**
         * @brief Logs an info message.
         *
         * The message will be written with "INFO" prefix.
         * @param message Message to log.
         */
        void LogInfo(const std::string& message);

    private:

        /**
         * @brief Internal enumeration of log types.
         */
        enum class LogType { Error, Warning, Info };

        /**
         * @brief Default path for the log file.
         */
        std::string logFilePath = "..\\UserLog.txt";

        /**
         * @brief Internal function to log a message with a specific type.
         *
         * @param message Message to log.
         * @param type Type of log (Info, Warning, Error). Defaults to Info.
         */
        void Log(const std::string& message, LogType type = LogType::Info);

        /**
         * @brief Writes a message directly to the log file.
         *
         * @param message Message to write.
         */
        void LogToFile(const std::string& message);
    };
} // namespace Engine