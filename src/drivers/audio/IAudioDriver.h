#pragma once

#include <stdint.h>
#include <stdbool.h>

// ✅ Audio Driver Interface
// All audio drivers (TDA7439, PT2322, PT2313, etc.) must implement this interface.

class IAudioDriver {
public:
    virtual ~IAudioDriver() = default;

    // 🔸 Initialize the audio IC (I2C setup, apply defaults, etc.)
    virtual void Init() = 0;

    // 🔸 Basic controls
    virtual void SetVolume(uint8_t volume) = 0;
    virtual void SetInput(uint8_t input) = 0;
    virtual void SetLoudness(bool enable) = 0;

    // 🔸 Optional EQ and sound adjustments
    virtual void SetBass(int8_t bass) = 0;
    virtual void SetTreble(int8_t treble) = 0;
    virtual void SetBalance(int8_t balance) = 0;

    // 🔸 Optionally support state queries (if needed)
    virtual uint8_t GetVolume() { return 0; }
    virtual uint8_t GetInput() { return 0; }
    virtual bool GetLoudness() { return false; }

    // 🔸 You can extend this in future (e.g., mute, bypass, gain control)
};
