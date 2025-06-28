#pragma once

#include "SettingsStruct.h"

class SettingsManager {
public:

    bool LoadSettings();
    void SaveSettings();
    void ResetToDefault();
    SettingsStruct Settings;
    static SettingsManager& Instance();

private:

    //static uint32_t CalculateCRC32(const uint8_t* data, size_t length);
    static bool LoadFromFlash();
    static bool SaveToFlash();
};
