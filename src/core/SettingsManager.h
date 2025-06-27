#pragma once
#include <ArduinoJson.h>
#include <FS.h>

class SettingsManager {
public:
    static bool Load();
    static bool Save();
    static JsonVariant Get(const char* key);
    static void Set(const char* key, JsonVariant value);

private:
    static DynamicJsonDocument doc;
    static const char* filename;
};
