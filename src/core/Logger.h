#pragma once
#include <Arduino.h>

enum class LogLevel { Debug, Info, Warn, Error };

class Logger {
public:
    static void Init();
    static void Log(LogLevel level, const char* tag, const char* fmt, ...);
    static void Debug(const char* tag, const char* fmt, ...);
    static void Info(const char* tag, const char* fmt, ...);
    static void Warn(const char* tag, const char* fmt, ...);
    static void Error(const char* tag, const char* fmt, ...);
    
    static void Error(const char* msg) { Error("LOG", "%s", msg); }
    static void Warn(const char* msg) { Warn("LOG", "%s", msg); }
    static void Info(const char* msg) { Info("LOG", "%s", msg); }

};
