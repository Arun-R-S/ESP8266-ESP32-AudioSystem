#include "AudioDriverManager.h"
#include "TDA7439Driver.h"
#include "core/SettingsStruct.h"
#include "core/Logger.h"

AudioDriverManager& AudioDriverManager::Instance() {
    static AudioDriverManager instance;
    return instance;
}

void AudioDriverManager::Init(I2CBus& bus) {
    if (strcmp(Settings.audio.activeDriver, "TDA7439") == 0) {
        activeDriver = new TDA7439Driver(bus, 0x44);
        activeDriver->Init();
        AddLogInfo("AudioDriverManager", "TDA7439 Driver Initialized");
    } else {
        AddLogError("AudioDriverManager", "No valid audio driver selected");
    }
}

IAudioDriver* AudioDriverManager::GetActiveDriver() {
    return activeDriver;
}
