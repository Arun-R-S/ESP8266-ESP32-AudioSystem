#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

// Log levels
#define LOG_LEVEL_NONE     0
#define LOG_LEVEL_ERROR    1
#define LOG_LEVEL_WARNING  2
#define LOG_LEVEL_INFO     3
#define LOG_LEVEL_DEBUG    4
#define LOG_LEVEL_VERBOSE  5

class Logger {
public:
    static void init(uint8_t level);

    static void error(const char* format, ...);
    static void warning(const char* format, ...);
    static void info(const char* format, ...);
    static void debug(const char* format, ...);
    static void verbose(const char* format, ...);

private:
    static uint8_t currentLogLevel;
    static void log(const char* level, uint8_t minLevel, const char* format, va_list args);
};

#endif // LOGGER_H
