#pragma once

#include "IAudioDriver.h"
#include "hal/I2CBus.h"
#include "core/StatusManager.h"
#include "core/Logger.h"

class TDA7418Driver : public IAudioDriver {
public:
    TDA7418Driver(I2CBus* bus, uint8_t address = 0x44);

    virtual bool begin() override;
    String GetDriverName() override { return "TDA7418"; }

    virtual bool SetVolume(int volume) override;
    virtual bool SetInput(uint8_t input) override;
    virtual bool SetTone(int bass, int middle, int treble) override;
    virtual bool SetLoudness(bool enable, uint8_t attenuation = 0) override;
    virtual bool SetSpeakerLevels(int fl, int fr, int rl, int rr, int sub) override;

    virtual bool hasMiddleControl() override { return true; }
    virtual bool hasSubwoofer() override { return true; }
    virtual bool hasLoudness() override { return true; }

private:
    I2CBus* _bus;
    uint8_t _address;
    uint8_t _registers[14];

    bool writeRegister(uint8_t reg, uint8_t value);
    bool batchWrite(uint8_t startReg, uint8_t* data, uint8_t length);

    uint8_t volumeToRegister(int value);
    uint8_t attenuationToRegister(int value);
    void resetRegisters();
};
