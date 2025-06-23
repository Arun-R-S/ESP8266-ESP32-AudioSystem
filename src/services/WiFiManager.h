#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32)
  #include <WiFi.h>
#endif

class WiFiManager {
public:
    static void begin(const char* hostname = "ESP-AudioSystem");
    static bool isConnected();
    static String getLocalIP();
};

#endif // WIFI_MANAGER_H
