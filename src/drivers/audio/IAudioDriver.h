#pragma once

#include <stdint.h>

enum class AudioFeature {
     Volume,
    Input,
    Bass,
    Treble,
    Balance,
    FrontLeft,
    FrontRight,
    RearLeft,
    RearRight,
    Center,
    Loudness,
    Subwoofer,
};

class IAudioDriver {
public:
    virtual ~IAudioDriver() = default;

    virtual bool Init() = 0;
    virtual const char* GetDriverName() = 0;

    virtual bool SetVolume(uint8_t value) = 0;
    virtual bool SetInput(uint8_t input) = 0;
    virtual bool SetBass(int8_t value) = 0;
    virtual bool SetTreble(int8_t value) = 0;
    virtual bool SetBalance(int8_t value) = 0;
    virtual bool Mute() = 0;

    virtual bool SupportsFeature(AudioFeature feature) = 0;
};
