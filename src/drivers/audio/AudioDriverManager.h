#pragma once

#include "IAudioDriver.h"

class AudioDriverManager {
public:
    static void RegisterDriver(IAudioDriver* driver);
    static IAudioDriver* GetActiveDriver();
    static bool HasFeature(AudioFeature feature);

private:
    static IAudioDriver* activeDriver;
};
