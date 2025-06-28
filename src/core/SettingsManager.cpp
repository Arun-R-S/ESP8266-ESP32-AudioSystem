#include "FlashFunctions.h"
#include "SettingsStruct.h"

#define SETTINGS_MAIN_ADDR  (0x7B000)
#define SETTINGS_BACKUP_ADDR (0x7C000)

SettingsStruct Settings;

bool LoadSettings() {
    SettingsStruct temp;
    if (FlashRead(SETTINGS_MAIN_ADDR, &temp, sizeof(temp))) {
        uint32_t crc = CalculateCRC32((uint8_t*)&temp + 4, sizeof(temp) - 4);
        if (crc == temp.crc32) {
            memcpy(&Settings, &temp, sizeof(temp));
            return true;
        }
    }

    // Try backup
    if (FlashRead(SETTINGS_BACKUP_ADDR, &temp, sizeof(temp))) {
        uint32_t crc = CalculateCRC32((uint8_t*)&temp + 4, sizeof(temp) - 4);
        if (crc == temp.crc32) {
            memcpy(&Settings, &temp, sizeof(temp));
            SaveSettings(); // restore main
            return true;
        }
    }

    // If both fail, reset to defaults
    ResetSettings();
    SaveSettings();
    return false;
}

void SaveSettings() {
    Settings.crc32 = CalculateCRC32((uint8_t*)&Settings + 4, sizeof(Settings) - 4);
    FlashWrite(SETTINGS_MAIN_ADDR, &Settings, sizeof(Settings));
    FlashWrite(SETTINGS_BACKUP_ADDR, &Settings, sizeof(Settings)); // Backup
}

void ResetSettings() {
    memset(&Settings, 0, sizeof(Settings));
    Settings.volume = 25;
    Settings.input = 1;
    Settings.loudness = true;
    strcpy(Settings.activeDriver, "TDA7439");
    strcpy(Settings.deviceName, "ESP-Audio");
}
