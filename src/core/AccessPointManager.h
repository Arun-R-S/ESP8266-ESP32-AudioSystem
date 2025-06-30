#pragma once

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32)
  #include <WiFi.h>
#endif

class AccessPointManager {
public:
    void Start(const char* ssid, const char* password = nullptr);
    void HandleClient();
    static AccessPointManager& Instance();
private:
    AccessPointManager() = default;
    AccessPointManager(const AccessPointManager&) = delete;
    void operator=(const AccessPointManager&) = delete;
};
