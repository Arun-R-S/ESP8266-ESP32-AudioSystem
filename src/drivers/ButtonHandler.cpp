#include "ButtonHandler.h"

AudioIC* ButtonHandler::_audioIC = nullptr;
LCDDisplay* ButtonHandler::_lcd = nullptr;

ButtonHandler::ButtonHandler()
  : _button1(&_config, BUTTON1_PIN),
    _button2(&_config, BUTTON2_PIN) {}

void ButtonHandler::begin() {
  Logger::info("Initializing ButtonHandler");

  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);

  _config.setEventHandler(handleEvent);
  _button1.init(BUTTON1_PIN);
  _button2.init(BUTTON2_PIN);
}

void ButtonHandler::update(AudioIC& audioIC, LCDDisplay& lcd) {
  _audioIC = &audioIC;
  _lcd = &lcd;
  _button1.check();
  _button2.check();
}

void ButtonHandler::handleEvent(AceButton* button, uint8_t eventType, uint8_t state) {
  if (eventType != AceButton::kEventReleased) return;

  uint8_t pin = button->getPin();

  Logger::debug("Button event on pin: %d", pin);

  if (pin == BUTTON1_PIN) {
    int vol = _audioIC->getVolume();
    _audioIC->setVolume(vol < 48 ? vol + 1 : 48);
    _lcd->printLine(1, "Vol Up");
  } else if (pin == BUTTON2_PIN) {
    int vol = _audioIC->getVolume();
    _audioIC->setVolume(vol > 0 ? vol - 1 : 0);
    _lcd->printLine(1, "Vol Down");
  }
}
