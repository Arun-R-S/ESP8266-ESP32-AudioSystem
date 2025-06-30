#pragma once

#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

enum class WiFiConnectionState {
    DISCONNECTED,
    CONNECTING,
    CONNECTED,
    AP_MODE
};

class WiFiManager {
public:
    void begin();
    void handle();
    bool isConnected();
    WiFiConnectionState getState() { return state; }

private:
    bool connectToWiFi();
    void startAPMode();

    WiFiConnectionState state = WiFiConnectionState::DISCONNECTED;
    unsigned long connectStartTime = 0;
    const unsigned long connectTimeout = 15000; // 15 seconds
};
