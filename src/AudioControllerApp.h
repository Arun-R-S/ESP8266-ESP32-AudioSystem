#pragma once
#include "LoggerService.h"
#include "LCDService.h"
#include "AudioService.h"
#include "ButtonService.h"

class AudioControllerApp {
private:
  LCDService lcd;
  AudioService audio;
  ButtonService button;

public:
  AudioControllerApp()
    : lcd(0x27, 16, 2), button(D1) {}

  void begin() {
    LoggerService::begin();
    lcd.begin();
    audio.begin();
    button.begin(&AudioControllerApp::onButtonEventStatic);
    Log.notice(F("App started.\n"));
  }

  void loop() {
    button.check();
  }

  static void onButtonEventStatic(AceButton* btn, uint8_t eventType, uint8_t buttonState) {
    // static context handler - forward to instance if needed
    Log.notice(F("Button event: %d\n"), eventType);
  }
};
