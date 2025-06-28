#pragma once
#include <Arduino.h>

// =======================
// Log Levels
// =======================
#define LOG_LEVEL_NONE       0
#define LOG_LEVEL_INFO       1
#define LOG_LEVEL_WARN       2
#define LOG_LEVEL_ERROR      3
#define LOG_LEVEL_DEBUG      4
#define LOG_LEVEL_DEBUG_MORE 5
#define LOG_LEVEL_CORE       6
#define LOG_LEVEL_SECRET     7

// =======================
// Current Log Level (Default INFO)
// =======================
extern uint8_t CurrentLogLevel;

// =======================
// Log Function With Tag
// =======================
void Logger(uint8_t level, const char* tag, const char* fmt, ...);

// =======================
// Log Macros (Shortcut)
// =======================
#define AddLogError(tag, fmt, ...)       Logger(LOG_LEVEL_ERROR, tag, fmt, ##__VA_ARGS__)
#define AddLogWarn(tag, fmt, ...)        Logger(LOG_LEVEL_WARN, tag, fmt, ##__VA_ARGS__)
#define AddLogInfo(tag, fmt, ...)        Logger(LOG_LEVEL_INFO, tag, fmt, ##__VA_ARGS__)
#define AddLogDebug(tag, fmt, ...)       Logger(LOG_LEVEL_DEBUG, tag, fmt, ##__VA_ARGS__)
#define AddLogDebugMore(tag, fmt, ...)   Logger(LOG_LEVEL_DEBUG_MORE, tag, fmt, ##__VA_ARGS__)
#define AddLogCore(tag, fmt, ...)        Logger(LOG_LEVEL_CORE, tag, fmt, ##__VA_ARGS__)
#define AddLog(tag, fmt, ...)            Logger(LOG_LEVEL_NONE, tag, fmt, ##__VA_ARGS__)
#define AddLogSecret(tag, fmt, ...)      Logger(LOG_LEVEL_SECRET, tag, fmt, ##__VA_ARGS__)
