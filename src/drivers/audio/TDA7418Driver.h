#pragma once
#include "IAudioDriver.h"
#include <Arduino.h>
#include <Wire.h>
//#include "AudioICBase.h"
//#include "Logger.h"
//#include "StatusManager.h"

class TDA7418Driver : public IAudioDriver {
public:
    TDA7418Driver(TwoWire& wire, uint8_t i2cAddress = 0x44);

    bool begin() override;
    String getChipName() override { return "TDA7418"; }

    // Core Functions
    bool setVolume(int volume) override;
    bool setInput(uint8_t input) override;
    bool setTone(int bass, int middle, int treble) override;
    bool setLoudness(bool enable, uint8_t attenuation = 0) override;
    bool setSpeakerLevels(int fl, int fr, int rl, int rr, int sub) override;

    // Additional Features
    bool setMiddleQ(uint8_t q);
    bool setBassQ(uint8_t q);
    bool setSoftMute(bool enable);
    bool setSmoothingFilter(bool enable);

private:
    TwoWire* _wire;
    uint8_t _i2cAddress;
    uint8_t _registerData[14] = {0};

    bool writeRegister(uint8_t reg, uint8_t value);
    bool batchWrite(uint8_t startReg, uint8_t* data, uint8_t length);
    bool updateRegister(uint8_t reg, uint8_t mask, uint8_t value);
};
