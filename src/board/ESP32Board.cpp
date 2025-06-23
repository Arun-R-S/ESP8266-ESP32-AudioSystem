#include "BoardInterface.h"
#include <WiFi.h>
#include <Wire.h>

class ESP32Board : public BoardInterface {
public:
    void setupI2C() override {
        Wire.begin(21, 22);  // ESP32 default pins
    }

    void setupWiFi() override {
        WiFi.mode(WIFI_STA);
        WiFi.begin("SSID", "PASS");
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
        }
    }

    const char* getBoardName() override {
        return "ESP32";
    }

    int getDefaultSDA() override { return 21; }
    int getDefaultSCL() override { return 22; }
};
