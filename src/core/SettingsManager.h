#pragma once

#include "SettingsStruct.h"
#include "ResponseManager.h"

class SettingsManager {
public:
    bool LoadSettings();
    void SaveSettings();
    void ResetToDefault();
    void GetSettings();
    SettingsStruct Settings;
    static SettingsManager& Instance();

private:
    ResponseManager _responseManager;
    SettingsManager() = default;
    SettingsManager(const SettingsManager&) = delete;
    void operator=(const SettingsManager&) = delete;
    
};
