#pragma once

#include "SettingsStruct.h"

class SettingsManager {
public:
    SettingsManager();

    bool LoadSettings();
    void SaveSettings();
    void ResetToDefault();
    SettingsStruct Settings;

private:

    static uint32_t CalculateCRC32(const uint8_t* data, size_t length);
    static bool LoadFromFlash();
    static bool SaveToFlash();
};
