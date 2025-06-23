#pragma once
#include <AceButton.h>
using namespace ace_button;

#ifndef D1
#define D1 5
#endif

#ifndef D2
#define D2 4
#endif

class ButtonHandler {
private:
  ButtonConfig buttonConfig;
  AceButton button1;
  AceButton button2;

public:
  ButtonHandler() : button1(&buttonConfig, D1), button2(&buttonConfig, D2) {}

  void begin(void (*callback)(AceButton*, uint8_t, uint8_t)) {
    pinMode(D1, INPUT_PULLUP);
    pinMode(D2, INPUT_PULLUP);
    buttonConfig.setEventHandler(callback);
  }

  void checkButtons() {
    button1.check();
    button2.check();
  }
};
