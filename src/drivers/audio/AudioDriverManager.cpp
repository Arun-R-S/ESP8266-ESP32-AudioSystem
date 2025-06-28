#include "AudioDriverManager.h"
#include "TDA7439Driver.h"
#include "core/SettingsStruct.h"
#include "core/Logger.h"
#include <string.h>

AudioDriverManager& AudioDriverManager::Instance() {
    static AudioDriverManager instance;
    return instance;
}

void AudioDriverManager::Init(I2CBus& bus) {
    if (strcmp(Settings.audio.activeDriver, "TDA7439") == 0) {
        activeDriver = new TDA7439Driver(bus, 0x44);
    }
    // (Future) else if (strcmp(Settings.audio.activeDriver, "PT2322") == 0) { ... }

    if (activeDriver != nullptr) {
        activeDriver->Init();
        AddLogInfo("ADM", "Audio driver initialized");
    } else {
        AddLogError("ADM", "No valid audio driver selected");
    }
}

IAudioDriver* AudioDriverManager::GetActiveDriver() {
    AddLogDebug("AudioDriverManager","GetActiveDrivers Start");
    return activeDriver;
}
