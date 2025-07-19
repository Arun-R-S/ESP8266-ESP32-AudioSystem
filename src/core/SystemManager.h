#pragma once
#include <Arduino.h>
#ifdef ESP8266

#else

#endif

class SystemManager {
public:
    static String GetUptimeString();
    static uint32_t GetTotalRam();
    static uint32_t GetFreeRam();
    static uint32_t GetUsedRam();
};
