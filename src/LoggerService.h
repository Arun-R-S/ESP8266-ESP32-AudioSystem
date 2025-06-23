#pragma once
#include <ArduinoLog.h>

class LoggerService {
public:
  static void begin(unsigned long baud = 115200) {
    Serial.begin(baud);
    while (!Serial) delay(10);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);
    Log.notice(F("Logger initialized.\n"));
  }
};
