#include "AudioDriverManager.h"
#include "core/Logger.h"

static IAudioDriver* activeDriver = nullptr;

void AudioDriverManager::RegisterDriver(IAudioDriver* driver) {
    if (!activeDriver) {
        activeDriver = driver;
        AddLogInfo("AudioDriverManager", "Driver '%s' registered.", driver->GetDriverName());
    }
}

IAudioDriver* AudioDriverManager::GetActiveDriver() {
    return activeDriver;
}

bool AudioDriverManager::SelectDriver(const char* driverName) {
    if (activeDriver && strcmp(activeDriver->GetDriverName(), driverName) == 0) {
        AddLogInfo("AudioDriverManager", "Driver '%s' selected.", driverName);
        return true;
    }
    AddLogError("AudioDriverManager", "Driver '%s' not found.", driverName);
    return false;
}

bool AudioDriverManager::HasFeature(AudioFeature feature) {
    if (!activeDriver) return false;
    return hasFeature(activeDriver->getSupportedFeatures(), feature);
}
