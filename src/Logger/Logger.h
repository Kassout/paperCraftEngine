#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <string>

/// Enumeration of the different type of log messages.
enum LogType {
    LOG_INFO,       // 0 (by default)
    LOG_WARNING,    // 1
    LOG_ERROR       // 2
};

/// Structure containing the information of a log message.
struct LogEntry {
    LogType type;
    std::string message;
};

/// Class responsible for building and displaying log messages on the console.
/// @file Logger.h
/// @author Maxime Héliot
/// @version 0.1.0 08/10/2021
class Logger {
public:
    /// Container of messages sent during the application session.
    static std::vector<LogEntry> messages;

    /// @brief Display log info message
    /// @details Build and display a log info message on the console.
    static void Log(const std::string& message);

    /// @brief Display log error message
    /// @details Build and display an error info message on the console.
    static void Err(const std::string& message);
};

#endif // LOGGER_H //
