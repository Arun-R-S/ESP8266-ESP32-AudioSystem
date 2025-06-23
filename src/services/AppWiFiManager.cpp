#include "AppWiFiManager.h"

void AppWiFiManager::begin(const char* hostname) {
#if defined(ESP8266)
  WiFi.mode(WIFI_STA);
#elif defined(ESP32)
  WiFi.mode(WIFI_MODE_STA);
#endif
  WiFi.begin();
  WiFi.setHostname(hostname);
}

bool AppWiFiManager::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}

String AppWiFiManager::getLocalIP() {
  return WiFi.localIP().toString();
}
