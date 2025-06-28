#pragma once

#include "SettingsStruct.h"

class SettingsManager {
public:
    static bool LoadSettings();
    static void SaveSettings();
    static void ResetToDefault();
    static SettingsStruct& Get();

private:
    static SettingsStruct Settings;

    static uint32_t CalculateCRC32(const uint8_t* data, size_t length);
    static bool LoadFromFlash();
    static bool SaveToFlash();
};
