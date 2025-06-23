#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <AceButton.h>
using namespace ace_button;

#include "../core/Logger.h"
#include "AudioIC.h"
#include "LCDDisplay.h"

// Fix D1/D2 not defined issue
#if defined(ESP8266)
  #define BUTTON1_PIN 5  // D1 = GPIO5 on NodeMCU
  #define BUTTON2_PIN 4  // D2 = GPIO4
#elif defined(ESP32)
  #define BUTTON1_PIN 21
  #define BUTTON2_PIN 22
#else
  #define BUTTON1_PIN 2
  #define BUTTON2_PIN 3
#endif

class ButtonHandler {
public:
  ButtonHandler();
  void begin();
  void update(AudioIC& audioIC, LCDDisplay& lcd);

private:
  static void handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState);

  static AudioIC* _audioIC;
  static LCDDisplay* _lcd;

  ButtonConfig _config;
  AceButton _button1;
  AceButton _button2;
};

#endif
