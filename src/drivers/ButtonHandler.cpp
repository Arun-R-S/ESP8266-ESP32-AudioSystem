#include "ButtonHandler.h"

AudioIC* ButtonHandler::_audioIC = nullptr;
LCDDisplay* ButtonHandler::_lcd = nullptr;

ButtonHandler::ButtonHandler()
  : _btn1(&_config, BUTTON1_PIN), _btn2(&_config, BUTTON2_PIN) {}

void ButtonHandler::begin() {
  Logger::info("Initializing ButtonHandler");
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  _config.setEventHandler(handleEvent);
}

void ButtonHandler::update(AudioIC& audioIC, LCDDisplay& lcd) {
  _audioIC = &audioIC;
  _lcd = &lcd;
  _btn1.check();
  _btn2.check();
}

void ButtonHandler::handleEvent(AceButton* button, uint8_t eventType, uint8_t state) {
  uint8_t pin = button->getPin();

  Logger::debug("Button event: pin=%d type=%d", pin, eventType);
  if (eventType == AceButton::kEventReleased) {
    if (pin == BUTTON1_PIN) {
      int vol = _audioIC->getVolume() + 1;
      _audioIC->setVolume(constrain(vol, 0, 48));
      _lcd->printLine(1, "Volume Up");
    } else if (pin == BUTTON2_PIN) {
      int vol = _audioIC->getVolume() - 1;
      _audioIC->setVolume(constrain(vol, 0, 48));
      _lcd->printLine(1, "Volume Down");
    }
  }
}
