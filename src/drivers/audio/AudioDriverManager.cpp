#include "AudioDriverManager.h"
#include "core/Logger.h"

IAudioDriver* AudioDriverManager::activeDriver = nullptr;

void AudioDriverManager::RegisterDriver(IAudioDriver* driver) {
    activeDriver = driver;
    AddLogInfo("AudioDriverManager", "Audio driver [%s] registered", driver->GetDriverName());
}

IAudioDriver* AudioDriverManager::GetActiveDriver() {
    return activeDriver;
}

bool AudioDriverManager::HasFeature(AudioFeature feature) {
    if (!activeDriver) return false;
    return activeDriver->SupportsFeature(feature);
}
