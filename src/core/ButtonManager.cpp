#include "ButtonManager.h"
#include "config/SettingsStruct.h"

#define DEBOUNCE_DELAY Settings.buttonSettings.debounceDelayTime
#define DOUBLE_CLICK_TIME Settings.buttonSettings.doubleClickTime
#define LONG_PRESS_TIME Settings.buttonSettings.holdTime

Button::Button(uint8_t pin, bool activeLow) :
    _pin(pin), _activeLow(activeLow), _lastState(false),
    _lastDebounceTime(0), _buttonDownTime(0), _buttonPressed(false),
    _clickCount(0) {
    pinMode(pin, INPUT_PULLUP);
}

void Button::AttachCallback(std::function<void(ButtonEvent)> callback) {
    _callback = callback;
}

void Button::Update() {
    bool reading = digitalRead(_pin) == (_activeLow ? LOW : HIGH);

    if (reading != _lastState) {
        _lastDebounceTime = millis();
    }

    if ((millis() - _lastDebounceTime) > DEBOUNCE_DELAY) {
        if (reading != _buttonPressed) {
            _buttonPressed = reading;

            if (_buttonPressed) {
                _buttonDownTime = millis();
                _clickCount++;
            } else {
                if ((millis() - _buttonDownTime) >= LONG_PRESS_TIME) {
                    if (_callback) _callback(ButtonEvent::LongPress);
                    _clickCount = 0;
                }
            }
        }
    }

    // Handle double click timing
    if (!_buttonPressed && _clickCount == 1) {
        if (millis() - _buttonDownTime > DOUBLE_CLICK_TIME) {
            if (_callback) _callback(ButtonEvent::SingleClick);
            _clickCount = 0;
        }
    } else if (_clickCount == 2) {
        if (_callback) _callback(ButtonEvent::DoubleClick);
        _clickCount = 0;
    }

    _lastState = reading;
}
