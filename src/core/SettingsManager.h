#pragma once

#include "SettingsStruct.h"

class SettingsManager {
public:
    const char* Module_TAG = "SettingsManager";
    const char* Friendly_TAG = "Settings";
    bool LoadSettings();
    void SaveSettings();
    void ResetToDefault();
    SettingsStruct Settings;
    static SettingsManager& Instance();

private:
    SettingsManager() = default;
    SettingsManager(const SettingsManager&) = delete;
    void operator=(const SettingsManager&) = delete;
    
};
