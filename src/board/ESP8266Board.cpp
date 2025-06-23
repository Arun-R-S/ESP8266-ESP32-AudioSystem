#include "BoardInterface.h"
#include <ESP8266WiFi.h>
#include <Wire.h>

class ESP8266Board : public BoardInterface {
public:
    void setupI2C() override {
        Wire.begin(D2, D1);  // ESP8266 default pins
    }

    void setupWiFi() override {
        WiFi.mode(WIFI_STA);
        WiFi.begin("SSID", "PASS");
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
        }
    }

    const char* getBoardName() override {
        return "ESP8266";
    }

    int getDefaultSDA() override { return D2; }
    int getDefaultSCL() override { return D1; }
};
