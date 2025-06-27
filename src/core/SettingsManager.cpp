#include "SettingsManager.h"
#include "Logger.h"
#include <LittleFS.h>

const char* SettingsManager::filename = "/settings.json";
DynamicJsonDocument SettingsManager::doc(2048);

bool SettingsManager::Load() {
    if (!LittleFS.begin()) {
        Logger::Error("Failed to mount LittleFS");
        return false;
    }

    File file = LittleFS.open(filename, "r");
    if (!file) {
        Logger::Warn("Settings file not found, using defaults");
        return false;
    }

    DeserializationError err = deserializeJson(doc, file);
    file.close();
    if (err) {
        Logger::Error("Failed to parse settings");
        return false;
    }

    Logger::Info("Settings loaded");
    return true;
}

bool SettingsManager::Save() {
    File file = LittleFS.open(filename, "w");
    if (!file) {
        Logger::Error("Failed to open settings file for writing");
        return false;
    }

    serializeJson(doc, file);
    file.close();
    Logger::Info("Settings saved");
    return true;
}

JsonVariant SettingsManager::Get(const char* key) {
    return doc[key];
}

void SettingsManager::Set(const char* key, JsonVariant value) {
    doc[key] = value;
}
