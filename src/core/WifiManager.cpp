#include "WiFiManager.h"
#include "AccessPointManager.h"
#include "config/SettingsStruct.h"
#include "core/Logger.h"

extern AccessPointManager APManager;

void WiFiManager::begin() {
    if (strlen(Settings.wifiSettings.ssid) == 0) {
        AddLogWarn("WifiManager", "No SSID configured. Starting AP.");
        startAPMode();
        return;
    }

    WiFi.mode(WIFI_STA);
    state = WiFiConnectionState::CONNECTING;
    connectStartTime = millis();
    WiFi.begin(Settings.wifiSettings.ssid, Settings.wifiSettings.password);

    AddLogInfo("WifiManager", "Connecting to WiFi SSID: %s", Settings.wifiSettings.ssid);
}

void WiFiManager::handle() {
    if (state == WiFiConnectionState::CONNECTING) {
        if (WiFi.status() == WL_CONNECTED) {
            AddLogInfo("WifiManager", "WiFi Connected! IP: %s", WiFi.localIP().toString().c_str());
            state = WiFiConnectionState::CONNECTED;
        } else if (millis() - connectStartTime > connectTimeout) {
            AddLogError("WifiManager", "WiFi connection failed. Switching to AP Mode.");
            startAPMode();
        }
    }

    if (state == WiFiConnectionState::CONNECTED && WiFi.status() != WL_CONNECTED) {
        AddLogError("WifiManager", "WiFi Lost Connection. Attempting reconnect.");
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
    state = WiFiConnectionState::AP_MODE;
}
