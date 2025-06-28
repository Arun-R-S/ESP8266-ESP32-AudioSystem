#pragma once

#include <Arduino.h>
#include <stdarg.h>

// =======================
// Log Levels
// =======================
enum LogLevel : uint8_t {
    LOG_LEVEL_NONE       = 0,
    LOG_LEVEL_INFO       = 1,
    LOG_LEVEL_WARN       = 2,
    LOG_LEVEL_ERROR      = 3,
    LOG_LEVEL_DEBUG      = 4,
    LOG_LEVEL_DEBUG_INFO = 5,
    LOG_LEVEL_DEBUG_MORE = 6,
    LOG_LEVEL_CORE       = 7,
    LOG_LEVEL_SECRET     = 8
};

class Logger {
public:
    // Initialize Logger with output stream and log level
    static void Begin(Stream& stream, LogLevel level = LOG_LEVEL_INFO);

    // Change log level at runtime
    static void SetLogLevel(LogLevel level);
    static LogLevel GetLogLevel();

    // Output destination (could be Serial, Telnet, etc.)
    static void SetOutput(Stream& stream);

    // Logging functions
    static void Log(LogLevel level, const char* tag, const char* fmt, ...);

    // Shortcut functions
    static void Info(const char* tag, const char* fmt, ...);
    static void Warn(const char* tag, const char* fmt, ...);
    static void Error(const char* tag, const char* fmt, ...);
    static void Debug(const char* tag, const char* fmt, ...);
    static void Core(const char* tag, const char* fmt, ...);
    static void Secret(const char* tag, const char* fmt, ...);

private:
    static Stream* _output;
    static LogLevel _currentLevel;

    static const char* LevelToString(LogLevel level);
    static void LogInternal(LogLevel level, const char* tag, const char* fmt, va_list args);
};


// =======================
// Log Macros (Shortcut)
// =======================
#define AddLogError(tag, fmt, ...)       Logger::Error(tag, fmt, ##__VA_ARGS__)
#define AddLogWarn(tag, fmt, ...)        Logger::Warn(tag, fmt, ##__VA_ARGS__)
#define AddLogInfo(tag, fmt, ...)        Logger::Info(tag, fmt, ##__VA_ARGS__)
#define AddLogDebug(tag, fmt, ...)       Logger::Debug(tag, fmt, ##__VA_ARGS__)
#define AddLogDebugMore(tag, fmt, ...)   Logger::Log(LOG_LEVEL_DEBUG_MORE, tag, fmt, ##__VA_ARGS__)
#define AddLogCore(tag, fmt, ...)        Logger::Core(tag, fmt, ##__VA_ARGS__)
#define AddLog(tag, fmt, ...)            Logger::Log(LOG_LEVEL_NONE, tag, fmt, ##__VA_ARGS__)
#define AddLogSecret(tag, fmt, ...)      Logger::Secret(tag, fmt, ##__VA_ARGS__)
#define AddLogDebugInfo(tag, fmt, ...)   Logger::Log(LOG_LEVEL_DEBUG_INFO, tag, fmt, ##__VA_ARGS__)
#define SetLoggerLevel(level)            Logger::SetLogLevel(level)
#define GetLoggerLevel()                 Logger::GetLogLevel()

