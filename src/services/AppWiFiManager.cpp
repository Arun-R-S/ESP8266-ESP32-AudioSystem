#include "AppWiFiManager.h"
#include <ESP8266WiFi.h>

AppWiFiManager::AppWiFiManager(AsyncWebServer &server)
  : _server(server) {}

void AppWiFiManager::begin() {
  WiFi.mode(WIFI_STA);
  WiFi.begin("yourSSID", "yourPASSWORD");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected: " + WiFi.localIP().toString());
  _server.begin();
}

void AppWiFiManager::handle() {
  // No-op for now; use for future events
}
