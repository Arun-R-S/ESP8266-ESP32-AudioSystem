#pragma once
#include <stdint.h>
#include "core/Logger.h"
#include "DeviceConfig.h"

struct AudioSettings {
    uint8_t volume = 10;
    uint8_t input = 0;
    int8_t treble = 0;
    int8_t bass = 0;
    int8_t balance = 0;
    bool loudness = false;
    char activeDriver[16] = "TDA7439";
};

struct ButtonSettings {
    uint16_t debounceDelayTime = 50;
    uint16_t holdTime = 1000;
    uint16_t doubleClickTime = 500;
};

struct SystemSettings {
    char deviceName[32] = "Default-Device";
};

struct LoggerSettings {
    LogLevel CurrentLogLevel = LOG_LEVEL_CORE;
};

struct WifiSettings {
    char ssid[64] = "";
    char password[64] = "";
    char hostname[32] = "ESP-Audio";
    bool dhcp = true;
    char staticIP[16] = "";
    char gateway[16] = "";
    char subnet[16] = "";
};

struct SettingsStruct {
    uint32_t crc32;  // Checksum for integrity

    AudioSettings audio;
    SystemSettings system;
    LoggerSettings logger;
    DeviceConfig_t DeviceConfig;
    ButtonSettings buttonSettings;
    WifiSettings wifiSettings;
    // Future expansions can be added here
    
};

extern SettingsStruct Settings; // Declare globally
