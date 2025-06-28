#pragma once

#include "SettingsStruct.h"

class SettingsManager {
public:
    static void Load();
    static void Save();
    static void ResetToDefault();
    static AppSettings& Get();

private:
    static AppSettings settings;

    static uint32_t CalculateCRC32(const uint8_t* data, size_t length);
    static bool LoadFromFlash();
    static bool SaveToFlash();
};
