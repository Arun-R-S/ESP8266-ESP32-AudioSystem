#pragma once
#include <stdint.h>

class AudioService {
public:
    void SetVolume(uint8_t volume);
    uint8_t GetVolume();

    void SetInput(uint8_t input);
    uint8_t GetInput();

    void SetLoudness(bool enabled);
    bool GetLoudness();

    void LoadFromSettings();
    void SaveToSettings();

private:
    void ApplyVolume();
    void ApplyInput();
    void ApplyLoudness();
};
