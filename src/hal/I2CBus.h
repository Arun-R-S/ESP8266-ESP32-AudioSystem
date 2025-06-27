#pragma once
#include <stdint.h>

class I2CBus {
public:
    I2CBus(uint8_t sda, uint8_t scl);
    bool Init();
    bool Write(uint8_t address, uint8_t reg, uint8_t data);
    bool Write(uint8_t address, const uint8_t* data, uint8_t length);
    void Scan();

private:
    uint8_t _sda;
    uint8_t _scl;
};
