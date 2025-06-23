#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

enum LogLevel {
    LOG_LEVEL_NONE = 0,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_VERBOSE
};

class Logger {
  public:
    static void init(LogLevel level);
    static void setLogLevel(LogLevel level);
    static void error(const char* format, ...);
    static void warning(const char* format, ...);
    static void info(const char* format, ...);
    static void verbose(const char* format, ...);
    static void debug(const char* format, ...);

  private:
    static LogLevel currentLogLevel;
    static void log(LogLevel level, const char* tag, const char* format, va_list args);
};

#endif
