#pragma once
#include "AudioDriver.h"

class AudioDriverManager {
public:
    static AudioDriverManager& Instance();

    void Init();
    AudioDriver* GetActiveDriver();

private:
    AudioDriverManager() = default;
    AudioDriver* activeDriver = nullptr;
};
