#include "AccessPointManager.h"
#include "core/Logger.h"

void AccessPointManager::start() {
    String ssid = "ESP-Audio-" + String(ESP.getChipId(), HEX);
    bool result = WiFi.softAP(ssid.c_str());

    if (result) {
        IPAddress IP = WiFi.softAPIP();
        AddLogInfo("AccessPointManager", "AP Started. SSID: %s | IP: %s", ssid.c_str(), IP.toString().c_str());
        active = true;
    } else {
        AddLogError("AccessPointManager", "Failed to start Access Point.");
        active = false;
    }
}

void AccessPointManager::stop() {
    if (active) {
        WiFi.softAPdisconnect(true);
        AddLogInfo("AccessPointManager", "Access Point stopped.");
        active = false;
    }
}
