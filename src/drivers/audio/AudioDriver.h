#pragma once

#include <stdint.h>

enum class AudioFeature {
    Volume,
    Bass,
    Treble,
    Loudness,
    Input,
    Balance,
    Surround,
};

class AudioDriver {
public:
    virtual bool Init() = 0;

    virtual bool SetVolume(uint8_t value) = 0;
    virtual bool SetBass(int8_t value) { return false; }
    virtual bool SetTreble(int8_t value) { return false; }
    virtual bool SetInput(uint8_t input) { return false; }
    virtual bool SetBalance(uint8_t channel, uint8_t value) { return false; }
    virtual bool SetLoudness(bool enable) { return false; }

    virtual bool SupportsFeature(AudioFeature feature) = 0;
    virtual const char* GetDriverName() = 0;

    virtual ~AudioDriver() {}
};
