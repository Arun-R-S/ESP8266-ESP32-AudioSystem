#include "HAL_GPIO.h"
#include "boards/Board_Definitions.h"
#include "core/Logger.h"

void HAL_GPIO::PinMode(uint8_t pin, uint8_t mode) {
    AddLogDebug("HAL_GPIO","Pin %d, PinMode %d",pin,mode);
    pinMode(pin, mode);
}

void HAL_GPIO::DigitalWrite(uint8_t pin, uint8_t value) {
    AddLogDebug("HAL_GPIO","DigitalWrite Pin %d, Value %d",pin,value);
    digitalWrite(pin, value);
}

int HAL_GPIO::DigitalRead(uint8_t pin) {
    int readVal = digitalRead(pin);
    AddLogDebug("HAL_GPIO","DigitalRead Pin %d, Value %d",pin,readVal);
    return readVal;
}

void HAL_GPIO::Toggle(uint8_t pin) {
    int readVal = digitalRead(pin);
    AddLogDebug("HAL_GPIO","Toggle Pin %d, Value %d",pin,!readVal);
    digitalWrite(pin, !readVal);
}
