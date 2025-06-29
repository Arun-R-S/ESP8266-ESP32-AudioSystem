#pragma once

#include "IAudioDriver.h"
#include "hal/I2CBus.h"

class AudioDriverManager {
public:
    static AudioDriverManager& Instance() {
        static AudioDriverManager instance;
        return instance;
    }   
    static void Init(I2CBus& bus);
    static IAudioDriver* GetDriver();
    static const char* GetCurrentDriverName();
    static const char* GetActiveDriver();
    static bool IsInitialized() { return _driver != nullptr; }

private:
    AudioDriverManager() {}  // Private constructor

    // Prevent copy
    AudioDriverManager(const AudioDriverManager&) = delete;
    AudioDriverManager& operator=(const AudioDriverManager&) = delete;

    static IAudioDriver* _driver;
};
