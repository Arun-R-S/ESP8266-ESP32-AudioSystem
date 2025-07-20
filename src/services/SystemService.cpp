#include "SystemService.h"

uint32_t millisToSeconds(uint32_t ms) {
    return ms / 1000;
}

String formatTime(uint32_t seconds) {
    uint32_t hrs = seconds / 3600;
    uint32_t mins = (seconds % 3600) / 60;
    uint32_t secs = seconds % 60;

    char buffer[16];
    sprintf(buffer, "%02lu:%02lu:%02lu", hrs, mins, secs);
    return String(buffer);
}

String SystemService::GetFormattedUptime() {
    return formatTime(millisToSeconds(millis()));
}

uint32_t SystemService::GetUptimeSeconds() {
    return millisToSeconds(millis());
}
