#include "HAL_I2C.h"

bool HAL_I2C::Begin(uint8_t sda, uint8_t scl, uint32_t speed) {
    Wire.begin(sda, scl, speed);
    return true;
}

bool HAL_I2C::WriteByte(uint8_t address, uint8_t reg, uint8_t data) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(data);
    return Wire.endTransmission() == 0;
}

bool HAL_I2C::ReadByte(uint8_t address, uint8_t reg, uint8_t* data) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0) return false;
    Wire.requestFrom(address, (uint8_t)1);
    if (Wire.available()) {
        *data = Wire.read();
        return true;
    }
    return false;
}

bool HAL_I2C::Write(uint8_t address, const uint8_t* data, size_t length) {
    Wire.beginTransmission(address);
    Wire.write(data, length);
    return Wire.endTransmission() == 0;
}

bool HAL_I2C::Read(uint8_t address, uint8_t* buffer, size_t length) {
    Wire.requestFrom(address, (uint8_t)length);
    size_t index = 0;
    while (Wire.available() && index < length) {
        buffer[index++] = Wire.read();
    }
    return index == length;
}

bool HAL_I2C::Ping(uint8_t address) {
    Wire.beginTransmission(address);
    return Wire.endTransmission() == 0;
}
