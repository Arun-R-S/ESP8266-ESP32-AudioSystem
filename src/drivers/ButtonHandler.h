#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <AceButton.h>
using namespace ace_button;

#include "../core/Logger.h"
#include "LCDDisplay.h"
#include "AudioIC.h"

#if defined(ESP8266)
  #define BUTTON1_PIN D1
  #define BUTTON2_PIN D2
#else
  #define BUTTON1_PIN 21
  #define BUTTON2_PIN 22
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
  AceButton _btn1;
  AceButton _btn2;
};

#endif
