#include "AudioService.h"
#include "core/Logger.h"
#include "core/SettingsStruct.h"
#include "core/SettingsManager.h"
#include "drivers/audio/AudioDriver.h"  // Your hardware driver class

const char* Module_TAG = "AudioService";
const char* FriendlyTag_TAG = "Audio";

void AudioService::SetVolume(uint8_t volume) {
    if (volume > 100) volume = 100;

    Settings.audio.volume = volume;
    AddLogInfo(Module_TAG, "Volume set to %d", volume);

    ApplyVolume();
    SettingsManager::Instance().SaveSettings();
}

uint8_t AudioService::GetVolume() {
    return Settings.audio.volume;
}

void AudioService::ApplyVolume() {
    AudioDriver::Instance().SetVolume(Settings.audio.volume);
}

// Same pattern for input
void AudioService::SetInput(uint8_t input) {
    Settings.audio.input = input;
    AddLogInfo(Module_TAG, "Input set to %d", input);

    ApplyInput();
    SettingsManager::Instance().SaveSettings();
}

void AudioService::ApplyInput() {
    AudioDriver::Instance().SetInput(Settings.audio.input);
}

// Same for loudness
void AudioService::SetLoudness(bool enabled) {
    Settings.audio.loudness = enabled;
    AddLogInfo(Module_TAG, "Loudness %s", enabled ? "ON" : "OFF");

    ApplyLoudness();
    SettingsManager::Instance().SaveSettings();
}

void AudioService::ApplyLoudness() {
    AudioDriver::Instance().SetLoudness(Settings.audio.loudness);
}

// Apply settings on boot
void AudioService::LoadFromSettings() {
    ApplyVolume();
    ApplyInput();
    ApplyLoudness();
}
