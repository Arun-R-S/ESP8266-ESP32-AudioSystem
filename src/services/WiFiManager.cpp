#include "WiFiManager.h"
#include <core/Logger.h>

#if defined(ESP8266)
  #include <DNSServer.h>
  #include <ESP8266WebServer.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#elif defined(ESP32)
  #include <DNSServer.h>
  #include <WebServer.h>
  #include <WiFiManager.h>
#endif

namespace {
  WiFiManager wifiManagerLib;
}

void WiFiManager::begin(const char* hostname) {
    Logger::info("WiFiManager: Starting...");

    WiFi.mode(WIFI_STA);
    WiFi.setHostname(hostname);

    if (!wifiManagerLib.autoConnect(hostname)) {
        Logger::error("WiFiManager: Failed to connect. Starting config portal...");
        // No connection, restart device
        delay(3000);
        ESP.restart();
    }

    Logger::info("WiFiManager: Connected successfully.");
    Logger::info("WiFiManager: IP Address: %s", WiFi.localIP().toString().c_str());
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

String WiFiManager::getLocalIP() {
    return WiFi.localIP().toString();
}
