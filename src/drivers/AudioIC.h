#pragma once

#include <TDA7439.h>
#include "../core/Logger.h"

class AudioIC {
public:
    AudioIC();

    bool begin();

    void loadSettings();
    void logSystemInfo();

    // Volume
    void setVolume(uint8_t volume);
    uint8_t getVolume() const;

    // Input
    void setInput(uint8_t input);
    uint8_t getInput() const;

    // Bass/Treble (using range 1=bass, 2=mid, 3=treble)
    void setBass(int8_t value);
    int8_t getBass() const;

    void setTreble(int8_t value);
    int8_t getTreble() const;

    void mute();

private:
    TDA7439 tda;

    uint8_t currentVolume = 20;
    uint8_t currentInput = 1;
    int8_t currentBass = 0;
    int8_t currentTreble = 0;
};
