#include <Arduino.h>
#include "SystemManager.h"

String SystemManager::GetUptimeString()
{
    unsigned long uptimeMillis = millis();
    unsigned long seconds = uptimeMillis / 1000;

    unsigned int days    = seconds / 86400;
    seconds %= 86400;

    unsigned int hours   = seconds / 3600;
    seconds %= 3600;

    unsigned int minutes = seconds / 60;
    seconds %= 60;

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%ud %02uh:%02um:%02us", days, hours, minutes, seconds);
    return String(buffer);
}

uint32_t SystemManager::GetTotalRam()
{
    #if defined(ESP8266)
        return 0; 
    #elif defined(ESP32)
        return ESP.getHeapSize();
    #else
        return 0;
    #endif
}

uint32_t SystemManager::GetUsedRam()
{
    #if defined(ESP8266)
        return ESP.getFreeHeap(); 
    #elif defined(ESP32)
        return ESP.getFreeHeap(); 
    #else
        return 0;
    #endif
}

uint32_t SystemManager::GetFreeRam()
{
    #if defined(ESP8266)
        return GetTotalRam() - GetUsedRam();
    #elif defined(ESP32)
        return GetTotalRam() - GetUsedRam();
    #else
        return 0;
    #endif
}