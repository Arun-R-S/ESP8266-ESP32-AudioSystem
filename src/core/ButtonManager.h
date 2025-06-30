#pragma once
#include <Arduino.h>
#include <functional>

enum class ButtonEvent {
    SingleClick,
    DoubleClick,
    LongPress
};

class Button {
public:
    Button(uint8_t pin, bool activeLow = true);

    void AttachCallback(std::function<void(ButtonEvent)> callback);
    void Update(); // Call this in loop()

private:
    uint8_t _pin;
    bool _activeLow;
    bool _lastState;
    unsigned long _lastDebounceTime;
    unsigned long _buttonDownTime;
    bool _buttonPressed;
    uint8_t _clickCount;
    std::function<void(ButtonEvent)> _callback;
};
