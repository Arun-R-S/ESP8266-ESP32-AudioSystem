#pragma once

#include <stdint.h>
#include <stdbool.h>

class IAudioDriver {
public:
    virtual ~IAudioDriver() = default;

    virtual void Init() = 0;
    virtual void SetVolume(uint8_t volume) = 0;
    virtual void SetInput(uint8_t input) = 0;
    virtual void SetLoudness(bool enable) = 0;
    virtual void SetBass(int8_t bass) = 0;
    virtual void SetTreble(int8_t treble) = 0;
    virtual void SetBalance(int8_t balance) = 0;
};
