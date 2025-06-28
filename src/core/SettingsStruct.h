#pragma once
#include <stdint.h>
#include "Logger.h"

struct AudioSettings {
    uint8_t volume = 10;
    uint8_t input = 0;
    int8_t treble = 0;
    int8_t bass = 0;
    int8_t balance = 0;
    bool loudness = false;
    char activeDriver[16] = "TDA7439";
};

struct SystemSettings {
    char deviceName[32] = "Default-Device";
};

struct LoggerSettings {
    uint8_t CurrentLogLevel = 7;
};

struct SettingsStruct {
    uint32_t crc32;  // Checksum for integrity

    AudioSettings audio;
    SystemSettings system;
    LoggerSettings logger;
    // Future expansions can be added here
};

extern SettingsStruct Settings; // Declare globally
