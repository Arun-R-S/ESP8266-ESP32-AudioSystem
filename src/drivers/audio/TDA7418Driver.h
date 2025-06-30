#pragma once

#include "IAudioDriver.h"
#include "hal/I2CBus.h"

#define TDA7418_ADDRESS 0x44

class TDA7418Driver : public IAudioDriver {
public:
    TDA7418Driver(I2CBus& bus);

    const char* GetDriverName() override { return "TDA7418"; }
    bool Init() override;

    bool SetVolume(uint8_t value) override;
    bool SetBass(int8_t value) override;
    bool SetMiddle(int8_t value);
    bool SetTreble(int8_t value) override;
    bool SetBalance(int8_t value) override;
    bool SetInput(uint8_t input) override;
    bool Mute() override;
    bool EnableLoudness(bool enable);

    AudioFeature GetSupportedFeatures() override;

private:
    I2CBus* _bus;
    bool WriteRegister(uint8_t reg, uint8_t data);
    uint8_t ConvertSoundValue(int8_t val);
};
