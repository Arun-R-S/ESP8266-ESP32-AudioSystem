#pragma once

#include "IAudioDriver.h"
#include "hal/I2CBus.h"

class TDA7439Driver : public IAudioDriver {
public:
    TDA7439Driver(I2CBus& bus, uint8_t address = 0x44);

    void Init() override;
    void SetVolume(uint8_t volume) override;
    void SetInput(uint8_t input) override;
    void SetLoudness(bool enable) override;
    void SetBass(int8_t bass) override;
    void SetTreble(int8_t treble) override;
    void SetBalance(int8_t balance) override;

private:
    I2CBus& _i2c;
    uint8_t _i2cAddress;
};
