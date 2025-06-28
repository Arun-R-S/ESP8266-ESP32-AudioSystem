#include "FlashFunctions.h"
#include "SettingsStruct.h"
#include "SettingsManager.h"
#include "Logger.h"

#define SETTINGS_MAIN_ADDR  (0x7B000)
#define SETTINGS_BACKUP_ADDR (0x7C000)

const char* Module_TAG = "SettingsManager";
const char* Friendly_TAG = "Settings";

void SettingsManager::SaveSettings() {
    AddLogDebug(Module_TAG, "Saving Settings");
    Settings.crc32 = CalculateCRC32((uint8_t*)&Settings + 4, sizeof(Settings) - 4);
    FlashWrite(SETTINGS_MAIN_ADDR, &Settings, sizeof(Settings));
    FlashWrite(SETTINGS_BACKUP_ADDR, &Settings, sizeof(Settings)); // Backup
}

void SettingsManager::ResetToDefault() {
    AddLogInfo(Module_TAG, "Resetting to default");
    memset(&Settings, 0, sizeof(Settings));
    Settings.audio.volume = 25;
    Settings.audio.input = 1;
    Settings.audio.loudness = true;
    strcpy(Settings.audio.activeDriver, "TDA7439");
    strcpy(Settings.system.deviceName, "ESP-Audio");
}

bool SettingsManager::LoadSettings() {
    AddLogInfo(Module_TAG, "Load Settings...");
    AddLogDebug(Module_TAG, "Retrieving from Flash...");
    SettingsStruct temp;
    if (FlashRead(SETTINGS_MAIN_ADDR, &temp, sizeof(temp))) {
        uint32_t crc = CalculateCRC32((uint8_t*)&temp + 4, sizeof(temp) - 4);
        if (crc == temp.crc32) {
            memcpy(&Settings, &temp, sizeof(temp));
            return true;
        }
    }
    AddLogDebug(Module_TAG, "Retrieving from Flash fails...");
    AddLogDebug(Module_TAG, "Retrieving from backup...");
    // Try backup
    if (FlashRead(SETTINGS_BACKUP_ADDR, &temp, sizeof(temp))) {
        uint32_t crc = CalculateCRC32((uint8_t*)&temp + 4, sizeof(temp) - 4);
        if (crc == temp.crc32) {
            memcpy(&Settings, &temp, sizeof(temp));
            SaveSettings(); // restore main
            return true;
        }
    }
    AddLogDebug(Module_TAG, "Retrieving from backup fails...");
    AddLogError(Module_TAG, "Failed to load settings....");
    // If both fail, reset to defaults
    ResetToDefault();
    SaveSettings();
    return false;
}




