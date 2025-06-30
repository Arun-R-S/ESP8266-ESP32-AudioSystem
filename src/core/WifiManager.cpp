#include "WiFiManager.h"
#include <WiFi.h>
#include "AccessPointManager.h"
#include "services/SettingsManager.h"
#include "core/Logger.h"

extern SettingsManager Settings;
extern AccessPointManager APManager;

void WiFiManager::begin() {
    if (strlen(Settings.data.wifiSettings.ssid) == 0) {
        AddLogWarn(LOG_WIFI, "No SSID configured. Starting AP.");
        startAPMode();
        return;
    }

    WiFi.mode(WIFI_STA);
    state = WiFiState::CONNECTING;
    connectStartTime = millis();
    WiFi.begin(Settings.data.wifiSettings.ssid, Settings.data.wifiSettings.password);

    AddLogInfo(LOG_WIFI, "Connecting to WiFi SSID: %s", Settings.data.wifiSettings.ssid);
}

void WiFiManager::handle() {
    if (state == WiFiState::CONNECTING) {
        if (WiFi.status() == WL_CONNECTED) {
            AddLogInfo(LOG_WIFI, "WiFi Connected! IP: %s", WiFi.localIP().toString().c_str());
            state = WiFiState::CONNECTED;
        } else if (millis() - connectStartTime > connectTimeout) {
            AddLogError(LOG_WIFI, "WiFi connection failed. Switching to AP Mode.");
            startAPMode();
        }
    }

    if (state == WiFiState::CONNECTED && WiFi.status() != WL_CONNECTED) {
        AddLogError(LOG_WIFI, "WiFi Lost Connection. Attempting reconnect.");
        begin();
    }
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::startAPMode() {
    WiFi.disconnect(true);
    WiFi.mode(WIFI_AP);
    APManager.start();
    state = WiFiState::AP_MODE;
}
