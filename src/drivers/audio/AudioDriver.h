#pragma once
#include <cstdint>

class AudioDriver {
public:
    virtual bool Init() = 0;
    virtual void SetVolume(int level) = 0;
    virtual void SetInput(uint8_t input) = 0;
    virtual void SetLoudness(bool enable) = 0;
    virtual void SetBass(int level) = 0;
    virtual void SetTreble(int level) = 0;
    virtual void SaveState() = 0;
    virtual void LoadState() = 0;
    virtual ~AudioDriver() {}
};
