// Logger.cpp
#include "Logger.h"
#include <Arduino.h>

LogLevel Logger::currentLevel = LOG_INFO;

void Logger::setLogLevel(LogLevel level) {
    currentLevel = level;
}

void Logger::error(const char* msg) {
    if (currentLevel >= LOG_ERROR) {
        Serial.println("[ERROR] " + String(msg));
    }
}

void Logger::warning(const char* msg) {
    if (currentLevel >= LOG_WARNING) {
        Serial.println("[WARNING] " + String(msg));
    }
}

void Logger::info(const char* msg) {
    if (currentLevel >= LOG_INFO) {
        Serial.println("[INFO] " + String(msg));
    }
}
