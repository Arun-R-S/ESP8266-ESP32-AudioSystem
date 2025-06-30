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
    
}

bool WiFiManager::connectToWiFi() {
    if (strlen(Settings.wifiSettings.ssid) == 0) {
        AddLogWarn("WiFi", "No SSID configured.");
        startAccessPoint();
        return false;
    }

    AddLogInfo("WiFi", "Connecting to %s...", Settings.wifiSettings.ssid);
    WiFi.begin(Settings.wifiSettings.ssid, Settings.wifiSettings.password);

    connectStart = millis();
    connecting = true;

    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 10) {
        delay(500);
        retries++;
        AddLogInfo("WifiManager", "Connecting...");
    }

    if (WiFi.status() == WL_CONNECTED) {
        AddLogInfo("WifiManager", "Connected. IP: %s", WiFi.localIP().toString().c_str());
        return true;
    } else {
        AddLogError("WifiManager", "WiFi connect failed.");
        startAccessPoint();
        return false;
    }
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

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::handle() {
    if (!isConnected() && !connecting) {
        connectToWiFi();
    }
}