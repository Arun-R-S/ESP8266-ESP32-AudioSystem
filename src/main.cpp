#include "board/BoardFactory.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "services/DashboardService.h"
#include "audio/AudioIC.h"

// Create server instance
AsyncWebServer server(80);
AudioIC audioIC;
DashboardService dashboard(server, audioIC);

BoardInterface* board;

void setup() {
    Serial.begin(115200);
    board = createBoard();
    Serial.println("Running on: " + String(board->getBoardName()));
    WiFi.begin("YourSSID", "YourPassword");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected");

    dashboard.setup();
}

void loop() {
    dashboard.update();
    delay(1000);
}
