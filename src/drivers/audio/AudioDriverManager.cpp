#include "AudioDriverManager.h"
#include "TDA7439Driver.h"
#include "core/Logger.h"
#include "core/SettingsStruct.h"

AudioDriverManager& AudioDriverManager::Instance() {
    static AudioDriverManager instance;
    return instance;
}

void AudioDriverManager::Init() {
    if (strcmp(Settings.audio.activeDriver, "TDA7439") == 0) {
        activeDriver = new TDA7439Driver();
        AddLogInfo("AudioDriverManager", "TDA7439 Driver initialized");
    }
    // Future:
    // else if (strcmp(Settings.audio.activeDriver, "PT2322") == 0) { ... }
    else {
        AddLogError("AudioDriverManager", "No valid Audio Driver found.");
    }
}

IAudioDriver* AudioDriverManager::GetActiveDriver() {
    return activeDriver;
}
