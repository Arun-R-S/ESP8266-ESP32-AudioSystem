#pragma once

#include <Arduino.h>

class HAL_EEPROM {
public:
    static bool Begin(size_t size = 512);
    static bool Read(size_t address, uint8_t* buffer, size_t length);
    static bool Write(size_t address, const uint8_t* data, size_t length);
    static bool Commit();
    static void End();
};
