#pragma once
#include <stdint.h>

class I2CBus {
public:
    I2CBus(uint8_t sda, uint8_t scl);

    bool Init();
    bool Write(uint8_t address, uint8_t reg, uint8_t data, uint8_t retries = 3);
    bool Write(uint8_t address, const uint8_t* data, uint8_t length, uint8_t retries = 3);
    bool Read(uint8_t address, uint8_t reg, uint8_t& data, uint8_t retries = 3);

    bool Detect(uint8_t address);

    static void Scan();

private:
    uint8_t _sda;
    uint8_t _scl;

    bool PerformWrite(uint8_t address, uint8_t reg, uint8_t data);
    bool PerformWrite(uint8_t address, const uint8_t* data, uint8_t length);
    bool PerformRead(uint8_t address, uint8_t reg, uint8_t& data);
};
