#include "Logger.h"
#include <stdarg.h>
#include <stdio.h>

void Logger::Init() {
    Serial.begin(115200);
    delay(100);
}

void Logger::Log(LogLevel level, const char* tag, const char* fmt, ...) {
    const char* levelStr = "";
    switch (level) {
        case LogLevel::Debug: levelStr = "DEBUG"; break;
        case LogLevel::Info:  levelStr = "INFO";  break;
        case LogLevel::Warn:  levelStr = "WARN";  break;
        case LogLevel::Error: levelStr = "ERROR"; break;
    }

    char buffer[256]; // Temp buffer for formatted string

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    Serial.printf("[%s][%s] %s\n", levelStr, tag, buffer);
}

void Logger::Debug(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    Log(LogLevel::Debug, tag, fmt, args);
    va_end(args);
}

void Logger::Info(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    Log(LogLevel::Info, tag, fmt, args);
    va_end(args);
}

void Logger::Warn(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    Log(LogLevel::Warn, tag, fmt, args);
    va_end(args);
}

void Logger::Error(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    Log(LogLevel::Error, tag, fmt, args);
    va_end(args);
}
