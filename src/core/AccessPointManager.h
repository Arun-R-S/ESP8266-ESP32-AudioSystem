#pragma once

#include <Arduino.h>

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <WebServer.h>
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
