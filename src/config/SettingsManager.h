#pragma once

#include "SettingsStruct.h"
#include "core/ResponseManager.h"



class SettingsManager {
public:
    bool LoadSettings();
    bool SaveSettings();
    void GetSettings();
    bool ResetSettingsToDefault();
    static SettingsManager& Instance();

private:
    ResponseManager _responseManager;
    SettingsManager() = default;
    SettingsManager(const SettingsManager&) = delete;
    void operator=(const SettingsManager&) = delete;
    
};
