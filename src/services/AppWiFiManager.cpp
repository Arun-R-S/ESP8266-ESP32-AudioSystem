#include "WiFiManager.h"  // Your renamed header
#include <core/Logger.h>

#if defined(ESP8266)
  #include <DNSServer.h>
  #include <ESP8266WebServer.h>
  #include <WiFiManager.h>
#elif defined(ESP32)
  #include <DNSServer.h>
  #include <WebServer.h>
  #include <WiFiManager.h>
#endif

namespace {
  ::WiFiManager wifiManagerLib;
}

void AppWiFiManager::begin(const char* hostname) {
    Logger::info("WiFiManager: Starting...");

    WiFi.mode(WIFI_STA);
    WiFi.setHostname(hostname);

    if (!wifiManagerLib.autoConnect(hostname)) {
        Logger::error("WiFiManager: Failed to connect. Starting config portal...");
        delay(3000);
        ESP.restart();
    }

    Logger::info("WiFiManager: Connected successfully.");
    Logger::info("WiFiManager: IP Address: %s", WiFi.localIP().toString().c_str());
}

bool AppWiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

String AppWiFiManager::getLocalIP() {
    return WiFi.localIP().toString();
}
