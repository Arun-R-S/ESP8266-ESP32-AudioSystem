#pragma once

#include "IAudioDriver.h"
#include "hal/I2CBus.h"

class AudioDriverManager {
public:
    static AudioDriverManager& Instance();

    void Init(I2CBus& bus);
    IAudioDriver* GetActiveDriver();

private:
    AudioDriverManager() = default;
    IAudioDriver* activeDriver = nullptr;
};
