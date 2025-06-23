#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>

#include "drivers/AudioIC.h"
#include "services/AppWiFiManager.h"
#include "services/DashboardService.h"

AsyncWebServer server(80);
AudioIC audioIC;
AppWiFiManager wifiManager(server);
DashboardService dashboardService(server, audioIC);

void setup() {
  Serial.begin(115200);
  audioIC.begin();
  wifiManager.begin();
  dashboardService.begin();
}

void loop() {
  wifiManager.handle();
  dashboardService.update();
}