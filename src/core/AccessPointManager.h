#pragma once

#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

class AccessPointManager {
public:
    void start();
    void stop();
    bool isActive() { return active; }

private:
    bool active = false;
};
