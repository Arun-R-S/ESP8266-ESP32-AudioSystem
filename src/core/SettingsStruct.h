#pragma once
#include <stdint.h>

struct AudioSettings {
    uint8_t volume;
    uint8_t input;
    bool loudness;
    char activeDriver[16];
};

struct SystemSettings {
    char deviceName[32];
};

struct SettingsStruct {
    uint32_t crc32;  // Checksum for integrity

    AudioSettings audio;
    SystemSettings system;

    // Future expansions can be added here
};

// Global instance
extern SettingsStruct Settings;
