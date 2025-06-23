#include "Logger.h"

LogLevel Logger::currentLogLevel = LOG_LEVEL_INFO;

void Logger::init(LogLevel level) {
    currentLogLevel = level;
    Serial.println("[Logger] Initialized");
}

void Logger::setLogLevel(LogLevel level) {
    currentLogLevel = level;
}

void Logger::log(LogLevel level, const char* tag, const char* format, va_list args) {
    if (level > currentLogLevel) return;

    Serial.print("[");
    Serial.print(tag);
    Serial.print("] ");

    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    Serial.println(buffer);
}

void Logger::error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log(LOG_LEVEL_ERROR, "ERROR", format, args);
    va_end(args);
}

void Logger::warning(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log(LOG_LEVEL_WARNING, "WARN", format, args);
    va_end(args);
}

void Logger::info(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log(LOG_LEVEL_INFO, "INFO", format, args);
    va_end(args);
}

void Logger::verbose(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log(LOG_LEVEL_VERBOSE, "VERBOSE", format, args);
    va_end(args);
}

void Logger::debug(const char* format, ...) {
    if (currentLogLevel < LOG_LEVEL_DEBUG) return;

    Serial.print("[DEBUG] ");
    va_list args;
    va_start(args, format);
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    Serial.print(buffer);
    va_end(args);
    Serial.println();
}

