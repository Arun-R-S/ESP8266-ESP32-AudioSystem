#include "WiFiManager.h"
#include "Logger.h"
#include "StatusManager.h"
#include "AccessPointManager.h"

void WiFiManager::begin() {
    AddLogInfo("WiFi", "Starting WiFiManager...");

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    connectToWiFi();
}

void WiFiManager::loop() {
    if (state == WiFiConnectionState::Connecting) {
        if (WiFi.status() == WL_CONNECTED) {
            AddLogInfo("WiFi", "Connected: %s", WiFi.localIP().toString().c_str());
            //StatusManager.SetWiFiConnected(true);
            state = WiFiConnectionState::Connected;
        } else if (millis() - lastRetryTime > retryInterval) {
            AddLogError("WiFi", "Retry failed. Switching to AP mode...");
            startAccessPoint();
        }
    }

    if (state == WiFiConnectionState::AccessPointMode) {
        AccessPointManager::Instance().HandleClient();
    }
}

void WiFiManager::connectToWiFi() {
    auto settings = Settings.wifiSettings;
    if (strlen(settings.ssid) == 0) {
        AddLogWarn("WiFi", "No SSID configured.");
        startAccessPoint();
        return;
    }

    AddLogInfo("WiFi", "Connecting to %s...", settings.ssid);

    WiFi.begin(settings.ssid, settings.password);
    state = WiFiConnectionState::Connecting;
    lastRetryTime = millis();
}

void WiFiManager::startAccessPoint() {
    String apName = "ESP-Audio-" + String(ESP.getChipId(), HEX);
    AddLogInfo("WiFi", "Starting Access Point: %s", apName.c_str());

    AccessPointManager::Instance().Start(apName.c_str(), "12345678");
    state = WiFiConnectionState::AccessPointMode;
}

WiFiConnectionState WiFiManager::getState() {
    return state;
}

String WiFiManager::getIP() {
    return WiFi.localIP().toString();
}
