#pragma once

#include "IAudioDriver.h"

class AudioDriverManager {
public:
    static void RegisterDriver(IAudioDriver* driver);
    static IAudioDriver* GetActiveDriver();
    static bool SelectDriver(const char* driverName);

    static bool HasFeature(AudioFeature feature);
};
