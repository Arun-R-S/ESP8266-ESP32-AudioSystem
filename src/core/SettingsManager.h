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
    SettingsManager() = default;
    SettingsManager(const SettingsManager&) = delete;
    void operator=(const SettingsManager&) = delete;
    
};
