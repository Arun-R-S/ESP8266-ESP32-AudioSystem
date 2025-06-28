#include "Logger.h"
#include <stdarg.h>

// =======================
// Default Log Level
// =======================
uint8_t CurrentLogLevel = LOG_LEVEL_DEBUG_MORE;

// =======================
// AddLog Implementation
// =======================
void Logger(uint8_t level, const char* tag, const char* fmt, ...) {
    if (level > CurrentLogLevel) {
        return; // Skip lower-level logs
    }

    char messageBuffer[256];

    va_list args;
    va_start(args, fmt);
    vsnprintf(messageBuffer, sizeof(messageBuffer), fmt, args);
    va_end(args);

    const char* levelStr = "";

    switch (level) {
        case LOG_LEVEL_ERROR:      levelStr = "ERROR";  break;
        case LOG_LEVEL_INFO:       levelStr = "INFO";   break;
        case LOG_LEVEL_DEBUG:      levelStr = "DEBUG";  break;
        case LOG_LEVEL_DEBUG_MORE: levelStr = "DEBUG+"; break;
        case LOG_LEVEL_WARN:       levelStr = "WARN";   break;
        case LOG_LEVEL_CORE:       levelStr = "CORE";   break;
        case LOG_LEVEL_SECRET:     levelStr = "SECRET"; break;
        default:                   levelStr = "LOG";    break;
    }

    // Output format: [INFO] Tag: message
    Serial.printf("[%s] %s: %s\n", levelStr, tag, messageBuffer);
}
