// === Project: ESP Audio Controller ===
// Supports: ESP8266 & ESP32
// Modules: TDA7439, AceButton, ESP-DASH, AutoConnect, EEPROM, LCD, MQTT/Home Assistant

#include "core/Logger.h"
#include "drivers/AudioIC.h"
#include "drivers/LCDDisplay.h"
#include "drivers/ButtonHandler.h"
#include "services/WiFiManager.h"
#include "services/DashboardService.h"

// === Platform Select ===
#if defined(ESP8266)
  #define DEVICE_TYPE "ESP8266"
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
  #include <EEPROM.h>
  #define USE_EEPROM
#elif defined(ESP32)
  #define DEVICE_TYPE "ESP32"
  #include <WiFi.h>
  #include <WebServer.h>
  #include <esp_partition.h>
#endif

#if defined(ESP8266)
ESP8266WebServer server(80);
#elif defined(ESP32)
WebServer server(80);
#endif

// === Global Instances ===
AudioIC audioIC;
LCDDisplay lcdDisplay;
ButtonHandler buttonHandler;
WiFiManagerService wifiManager(server);
DashboardService dashboardService(server);

// === Setup ===
void setup() {
  Serial.begin(115200);
  Wire.begin();
  Logger::init(LOG_LEVEL_VERBOSE);

  Logger::info("Booting device: %s", DEVICE_TYPE);

  lcdDisplay.begin();
  buttonHandler.begin();
  audioIC.begin();

  audioIC.loadSettings();
  wifiManager.begin();

  dashboardService.setup(audioIC);
  server.begin();
  Logger::info("Web server started");

  audioIC.logSystemInfo();
}

// === Loop ===
void loop() {
  buttonHandler.update(audioIC, lcdDisplay);
  wifiManager.handle();
  dashboardService.update(audioIC);
}
