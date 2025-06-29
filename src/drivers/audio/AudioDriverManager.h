#pragma once

#include "IAudioDriver.h"
#include "hal/I2CBus.h"

class AudioDriverManager {
public:
    static void Init(I2CBus& bus);
    static IAudioDriver* GetDriver();
    static const char* GetCurrentDriverName();

private:
    static IAudioDriver* _driver;
};
