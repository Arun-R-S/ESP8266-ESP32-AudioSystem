#pragma once

#include <Arduino.h>

class HAL_GPIO {
public:
    static void PinMode(uint8_t pin, uint8_t mode);
    static void DigitalWrite(uint8_t pin, uint8_t value);
    static int DigitalRead(uint8_t pin);
    static void Toggle(uint8_t pin);
};
