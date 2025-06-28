#pragma once

#include "IAudioDriver.h"
#include "hal/I2CBus.h"
#include "core/ResponseManager.h"

class AudioDriverManager {
public:
    static AudioDriverManager& Instance();

    void Init(I2CBus& bus);
    IAudioDriver* GetActiveDriver();

private:
    ResponseManager _responseManager;
    AudioDriverManager() = default;
    IAudioDriver* activeDriver = nullptr;
};
