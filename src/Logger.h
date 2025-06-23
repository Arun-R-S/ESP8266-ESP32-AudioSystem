#pragma once
#include <Arduino.h>

class Logger {
public:
  void begin(unsigned long baud = 115200) {
    Serial.begin(baud);
    delay(100); // Give time for Serial to initialize
  }

  void info(const char* message) {
    Serial.print("[INFO] ");
    Serial.println(message);
  }

  void debug(const char* message) {
    Serial.print("[DEBUG] ");
    Serial.println(message);
  }

  void error(const char* message) {
    Serial.print("[ERROR] ");
    Serial.println(message);
  }
};
