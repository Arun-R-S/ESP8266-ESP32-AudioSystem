#include "Logger.h"

uint8_t Logger::currentLogLevel = LOG_LEVEL_NONE;

void Logger::init(uint8_t level) {
    currentLogLevel = level;
    Serial.println();
    Serial.println("Logger initialized.");
}

void Logger::log(const char* level, uint8_t minLevel, const char* format, va_list args) {
    if (currentLogLevel < minLevel) return;

    char message[256];
    vsnprintf(message, sizeof(message), format, args);

    Serial.print("[");
    Serial.print(level);
    Serial.print("] ");
    Serial.println(message);
}

void Logger::error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log("ERROR", LOG_LEVEL_ERROR, format, args);
    va_end(args);
}

void Logger::warning(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log("WARN", LOG_LEVEL_WARNING, format, args);
    va_end(args);
}

void Logger::info(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log("INFO", LOG_LEVEL_INFO, format, args);
    va_end(args);
}

void Logger::debug(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log("DEBUG", LOG_LEVEL_DEBUG, format, args);
    va_end(args);
}

void Logger::verbose(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log("VERBOSE", LOG_LEVEL_VERBOSE, format, args);
    va_end(args);
}
