// Logger.h
#pragma once

enum LogLevel {
    LOG_NONE = 0,
    LOG_ERROR = 1,
    LOG_WARNING = 2,
    LOG_INFO = 3
};

class Logger {
  public:
    static void setLogLevel(LogLevel level);
    static void error(const char* msg);
    static void warning(const char* msg);
    static void info(const char* msg);

  private:
    static LogLevel currentLevel;
};
