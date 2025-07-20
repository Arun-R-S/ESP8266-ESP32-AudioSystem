#pragma once

#include <Arduino.h>

class SystemService {
public:
    static String GetFormattedUptime();
    static uint32_t GetUptimeSeconds();
};
