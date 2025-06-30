#include "core/FlashFunctions.h"
#include "SettingsStruct.h"
#include "SettingsManager.h"
#include "core/Logger.h"
#include "DeviceConfig.h"

#define SETTINGS_MAIN_ADDR  (0x7B000)
#define SETTINGS_BACKUP_ADDR (0x7C000)

SettingsStruct Settings;  // Define exactly once

SettingsManager& SettingsManager::Instance() {
    static SettingsManager instance;
    return instance;
}

bool SettingsManager::SaveSettings() {
    AddLogDebug("SettingsManager", "Saving Settings");
    Settings.crc32 = CalculateCRC32((uint8_t*)&Settings + 4, sizeof(Settings) - 4);
    AddLogCore("SettingsManager", "FlashWrite Main Block 0x%08X",SETTINGS_MAIN_ADDR);
    if(!FlashWrite(SETTINGS_MAIN_ADDR, &Settings, sizeof(Settings)))
    {
        AddLogError("SettingsManager", "Failed to FlashWrite in Main Block 0x%08X",SETTINGS_MAIN_ADDR);
        return false;
    }
    AddLogCore("SettingsManager", "FlashWrite Backup Block 0x%08X",SETTINGS_BACKUP_ADDR);
    if(!FlashWrite(SETTINGS_BACKUP_ADDR, &Settings, sizeof(Settings))) // Backup
    {
        AddLogCore("SettingsManager", "Failed to FlashWrite in Backup Block 0x%08X",SETTINGS_BACKUP_ADDR);
        return false;
    }
    return true;
}

bool SettingsManager::ResetSettingsToDefault() {
    AddLogInfo("SettingsManager", "Reset Settings to default values");
    // Create new instance with C++ defaults
    Settings = SettingsStruct();
    Settings.DeviceConfig = DefaultDeviceConfig;
    if(SaveSettings())
    {
        return true;
    }
    else{
        return false;
    }
}

void SettingsManager::GetSettings(){
    this->_responseManager.Clear();
    this->_responseManager.Append("{\"audio\":{");
    this->_responseManager.Append("\"volume\":%d,", Settings.audio.volume);
    this->_responseManager.Append("\"input\":%d,", Settings.audio.input);
    this->_responseManager.Append("\"loudness\":%s,", Settings.audio.loudness ? "true" : "false");
    this->_responseManager.Append("\"activeDriver\":\"%s\"},", Settings.audio.activeDriver);
    this->_responseManager.Append("\"logger\":{\"currentLogLevel\":\"%d\"},", Settings.logger.CurrentLogLevel);
    this->_responseManager.Append("\"system\":{\"deviceName\":\"%s\"},", Settings.system.deviceName);

    this->_responseManager.Append("\"crc32\":\"0x%08X\"}", Settings.crc32);

    AddLogInfo("Settings", "JSON: %s", this->_responseManager.Get());
}

bool SettingsManager::LoadSettings() {
    AddLogInfo("SettingsManager", "Load Settings...");
    AddLogDebug("SettingsManager", "Retrieving from Flash...");
    SettingsStruct temp;
    if (FlashRead(SETTINGS_MAIN_ADDR, &temp, sizeof(temp))) {
        uint32_t crc = CalculateCRC32((uint8_t*)&temp + 4, sizeof(temp) - 4);
        if (crc == temp.crc32) {
            memcpy(&Settings, &temp, sizeof(temp));
            AddLogDebug("SettingsManager", "Retrieved from Main Block...");
            //GetSettings();
            return true;
        }
    }
    AddLogDebug("SettingsManager", "Retrieving from Flash fails...");
    AddLogDebug("SettingsManager", "Retrieving from backup...");
    // Try backup
    if (FlashRead(SETTINGS_BACKUP_ADDR, &temp, sizeof(temp))) {
        uint32_t crc = CalculateCRC32((uint8_t*)&temp + 4, sizeof(temp) - 4);
        if (crc == temp.crc32) {
            memcpy(&Settings, &temp, sizeof(temp));
            AddLogDebug("SettingsManager", "Retrieved from Backup...");
            AddLogDebug("SettingsManager", "Restoring to Main Block...");
            SaveSettings(); // restore main
            return true;
        }
    }
    AddLogDebug("SettingsManager", "Retrieving from backup fails...");
    AddLogError("SettingsManager", "Failed to load settings....");
    // If both fail, reset to defaults
    ResetSettingsToDefault();
    SaveSettings();
    return false;
}




