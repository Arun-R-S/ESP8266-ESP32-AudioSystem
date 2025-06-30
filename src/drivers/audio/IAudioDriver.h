#pragma once

#include <stdint.h>

enum class SupportedFeature : uint16_t {
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

inline SupportedFeatures operator|(SupportedFeatures a, SupportedFeatures b) {
    return static_cast<SupportedFeatures>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
}

inline bool hasFeature(SupportedFeatures value, SupportedFeatures flag) {
    return (static_cast<uint16_t>(value) & static_cast<uint16_t>(flag)) != 0;
}

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

    virtual SupportedFeatures getSupportedFeatures() { return SupportedFeatures::None; }
};
