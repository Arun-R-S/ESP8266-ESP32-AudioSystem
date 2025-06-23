#include "ButtonHandler.h"

// Static instances
AudioIC* ButtonHandler::_audioIC = nullptr;
LCDDisplay* ButtonHandler::_lcd = nullptr;

ButtonHandler::ButtonHandler()
  : _btn1(&_config, BUTTON1_PIN), _btn2(&_config, BUTTON2_PIN) {
}

void ButtonHandler::begin() {
  Logger::info("Initializing ButtonHandler");

  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);

  _config.setEventHandler(handleEvent);

  Logger::info("ButtonHandler initialized on pins %d, %d", BUTTON1_PIN, BUTTON2_PIN);
}

void ButtonHandler::update(AudioIC& audioIC, LCDDisplay& lcd) {
  _audioIC = &audioIC;
  _lcd = &lcd;

  try {
    _btn1.check();
    _btn2.check();
  } catch (...) {
    Logger::error("Exception in ButtonHandler::update()");
  }
}

void ButtonHandler::handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  uint8_t pin = button->getPin();

  try {
    Logger::debug("Button event on pin %d: type=%d, state=%d", pin, eventType, buttonState);

    if (eventType == AceButton::kEventReleased) {
      if (pin == BUTTON1_PIN) {
        _audioIC->adjustVolume(+1); // Unified method
        _lcd->printLine("Volume Up", 1);
      } else if (pin == BUTTON2_PIN) {
        _audioIC->adjustVolume(-1);
        _lcd->printLine("Volume Down", 1);
      }
    }
  } catch (...) {
    Logger::error("Exception in ButtonHandler::handleEvent()");
  }
}
