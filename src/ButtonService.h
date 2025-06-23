#pragma once
#include <AceButton.h>
using namespace ace_button;

class ButtonService {
private:
  AceButton button;
  ButtonConfig config;
  uint8_t pin;

public:
  ButtonService(uint8_t btnPin) : button(&config), pin(btnPin) {}

  void begin(void (*callback)(AceButton*, uint8_t, uint8_t)) {
    pinMode(pin, INPUT_PULLUP);
    config.setEventHandler(callback);
    button.init(pin);
  }

  void check() {
    button.check();
  }
};
