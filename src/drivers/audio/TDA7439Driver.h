#pragma once
#include "AudioDriver.h"
#include "../../hal/I2CBus.h"

class TDA7439Driver : public AudioDriver {
public:
    TDA7439Driver(I2CBus& bus, uint8_t address);
    bool Init() override;
    void SetVolume(int level) override;
    void SetInput(uint8_t input) override;
    void SetLoudness(bool enable) override;
    void SetBass(int level) override;
    void SetTreble(int level) override;
    void SaveState() override;
    void LoadState() override;

private:
    I2CBus& _i2c;
    uint8_t _address;

    void WriteRegister(uint8_t reg, uint8_t value);
};
