#pragma once

#include "IAudioDriver.h"
#include "hal/I2CBus.h"

#define PT2322_ADDRESS 0x44

class PT2322Driver : public IAudioDriver {
public:
    PT2322Driver(I2CBus& bus);

    const char* GetDriverName() override { return "PT2322"; }
    bool Init() override;

    bool SetVolume(uint8_t value) override;
    bool SetInput(uint8_t input) override;

    AudioFeature GetSupportedFeatures() override;
    bool SupportsFeature(AudioFeature feature) override;

private:
    I2CBus* _bus;
    bool WriteRegister(uint8_t reg, uint8_t data);
};
