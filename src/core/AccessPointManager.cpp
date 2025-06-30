#include "AccessPointManager.h"
#include <WiFi.h>
#include "core/Logger.h"

void AccessPointManager::start() {
    String ssid = "ESP-Audio-" + String(ESP.getChipId(), HEX);
    bool result = WiFi.softAP(ssid.c_str());

    if (result) {
        IPAddress IP = WiFi.softAPIP();
        AddLogInfo(LOG_WIFI, "AP Started. SSID: %s | IP: %s", ssid.c_str(), IP.toString().c_str());
        active = true;
    } else {
        AddLogError(LOG_WIFI, "Failed to start Access Point.");
        active = false;
    }
}

void AccessPointManager::stop() {
    if (active) {
        WiFi.softAPdisconnect(true);
        AddLogInfo(LOG_WIFI, "Access Point stopped.");
        active = false;
    }
}
