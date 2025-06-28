#pragma once

#include <Arduino.h>
#include <Wire.h>

class HAL_I2C {
public:
    static bool Begin(uint8_t sda, uint8_t scl, uint32_t speed = 100000);
    static bool WriteByte(uint8_t address, uint8_t reg, uint8_t data);
    static bool ReadByte(uint8_t address, uint8_t reg, uint8_t* data);
    static bool Write(uint8_t address, const uint8_t* data, size_t length);
    static bool Read(uint8_t address, uint8_t* buffer, size_t length);
    static bool Ping(uint8_t address);
};
