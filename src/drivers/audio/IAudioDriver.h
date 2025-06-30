#pragma once

#include "AudioFeature.h"

class IAudioDriver {
public:
    virtual ~IAudioDriver() {}

    virtual const char* GetDriverName() = 0;
    virtual bool begin() = 0;

    // Capability Advertisement
    virtual AudioFeature getSupportedFeatures() { return AudioFeature::None; }

    // Functional APIs
    virtual bool SetVolume(int volume) { return false; }
    virtual bool SetTone(int bass, int middle, int treble) { return false; }
    virtual bool SetLoudness(bool enable, uint8_t attenuation = 0) { return false; }
    virtual bool SetInput(uint8_t input) { return false; }
    virtual bool SetSpeakerLevels(int fl, int fr, int rl, int rr, int sub) { return false; }
};
