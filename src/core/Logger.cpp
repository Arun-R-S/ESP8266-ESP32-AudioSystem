#include "Logger.h"

// Initialize static members
Stream* Logger::_output = nullptr;
LogLevel Logger::_currentLevel = LOG_LEVEL_INFO;

void Logger::Begin(Stream& stream, LogLevel level) {
    _output = &stream;
    _currentLevel = level;
}

void Logger::SetLogLevel(LogLevel level) {
    _currentLevel = level;
}

LogLevel Logger::GetLogLevel() {
    return _currentLevel;
}

void Logger::SetOutput(Stream& stream) {
    _output = &stream;
}

const char* Logger::LevelToString(LogLevel level) {
    switch (level) {
        case LOG_LEVEL_ERROR:      return "ERROR";
        case LOG_LEVEL_WARN:       return "WARN";
        case LOG_LEVEL_INFO:       return "INFO";
        case LOG_LEVEL_DEBUG:      return "DEBUG";
        case LOG_LEVEL_DEBUG_INFO: return "DEBUG_INFO";
        case LOG_LEVEL_DEBUG_MORE: return "DEBUG_MORE";
        case LOG_LEVEL_CORE:       return "CORE";
        case LOG_LEVEL_SECRET:     return "SECRET";
        default:                   return "LOG";
    }
}

void Logger::LogInternal(LogLevel level, const char* tag, const char* fmt, va_list args) {
    if (!_output || level > _currentLevel) {
        return;
    }

    char messageBuffer[256];
    vsnprintf(messageBuffer, sizeof(messageBuffer), fmt, args);

    _output->printf("[%s] %s: %s\n", LevelToString(level), tag, messageBuffer);
}

// ========================
// Public APIs
// ========================

void Logger::Log(LogLevel level, const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    LogInternal(level, tag, fmt, args);
    va_end(args);
}

void Logger::Info(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    LogInternal(LOG_LEVEL_INFO, tag, fmt, args);
    va_end(args);
}

void Logger::Warn(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    LogInternal(LOG_LEVEL_WARN, tag, fmt, args);
    va_end(args);
}

void Logger::Error(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    LogInternal(LOG_LEVEL_ERROR, tag, fmt, args);
    va_end(args);
}

void Logger::Debug(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    LogInternal(LOG_LEVEL_DEBUG, tag, fmt, args);
    va_end(args);
}

void Logger::Core(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    LogInternal(LOG_LEVEL_CORE, tag, fmt, args);
    va_end(args);
}

void Logger::Secret(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    LogInternal(LOG_LEVEL_SECRET, tag, fmt, args);
    va_end(args);
}
