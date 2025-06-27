#include "SettingsManager.h"
#include "Logger.h"
#include <LittleFS.h>

const char* SettingsManager::filename = "/settings.json";
DynamicJsonDocument SettingsManager::doc(2048);

bool SettingsManager::Load() {
    if (!LittleFS.begin()) {
        AddLogError("SettingsManager","Failed to mount LittleFS");
        return false;
    }

    File file = LittleFS.open(filename, "r");
    if (!file) {
        AddLogWarn("SettingsManager","Settings file not found, using defaults");
        return false;
    }

    DeserializationError err = deserializeJson(doc, file);
    file.close();
    if (err) {
        AddLogError("SettingsManager","Failed to parse settings");
        return false;
    }

    AddLogInfo("SettingsManager","Settings loaded");
    return true;
}

bool SettingsManager::Save() {
    File file = LittleFS.open(filename, "w");
    if (!file) {
        AddLogError("SettingsManager","Failed to open settings file for writing");
        return false;
    }

    serializeJson(doc, file);
    file.close();
    AddLogInfo("SettingsManager","Settings saved");
    return true;
}

JsonVariant SettingsManager::Get(const char* key) {
    return doc[key];
}

void SettingsManager::Set(const char* key, JsonVariant value) {
    doc[key] = value;
}
