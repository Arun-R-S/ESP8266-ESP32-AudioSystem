#pragma once

#include <Arduino.h>

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32)
  #include <WiFi.h>
#endif

#include "AccessPointManager.h"
#include "core/Logger.h"
#include "core/StatusManager.h"
#include "config/SettingsManager.h"

enum class WiFiConnectionState {
    Disconnected,
    Connecting,
    Connected,
    AccessPointMode
};

class WiFiManager {
public:
    void begin();
    void loop();

    WiFiConnectionState getState();
    String getIP();

    bool isConnected();

    void handle();

private:
    bool connectToWiFi();
    void startAccessPoint();
    void handleConnectionResult();

    WiFiConnectionState state = WiFiConnectionState::Disconnected;
    unsigned long retryInterval = 10000;
    unsigned long lastRetryTime = 0;

    unsigned long connectStart = 0;
    bool connecting = false;
};
