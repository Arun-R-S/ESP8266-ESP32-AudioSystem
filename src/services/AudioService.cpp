#include "AudioService.h"
#include "core/Logger.h"
#include "core/SettingsStruct.h"
#include "core/SettingsManager.h"  // Your hardware driver class
#include "drivers/audio/AudioDriverManager.h"


void AudioService::SetVolume(uint8_t volume) {
    if (volume > 100) volume = 100;

    Settings.audio.volume = volume;
    AddLogInfo("AudioService", "Volume set to %d", volume);

    ApplyVolume();
    SettingsManager::Instance().SaveSettings();
}

uint8_t AudioService::GetVolume() {
    return Settings.audio.volume;
}

void AudioService::ApplyVolume() {
    AddLogDebug("AudioService", "Apply Volume Start");
    AudioDriverManager::Instance().GetActiveDriver()->SetVolume(Settings.audio.volume);
    AddLogDebug("AudioService", "Apply Volume End");
}

// Same pattern for input
void AudioService::SetInput(uint8_t input) {
    Settings.audio.input = input;
    AddLogInfo("AudioService", "Input set to %d", input);

    ApplyInput();
    SettingsManager::Instance().SaveSettings();
}

void AudioService::ApplyInput() {
    AudioDriverManager::Instance().GetActiveDriver()->SetInput(Settings.audio.input);
}

// Same for loudness
void AudioService::SetLoudness(bool enabled) {
    Settings.audio.loudness = enabled;
    AddLogInfo("AudioService", "Loudness %s", enabled ? "ON" : "OFF");

    ApplyLoudness();
    SettingsManager::Instance().SaveSettings();
}

void AudioService::ApplyLoudness() {
    AudioDriverManager::Instance().GetActiveDriver()->SetLoudness(Settings.audio.loudness);
}

// Apply settings on boot
void AudioService::LoadFromSettings() {
    ApplyVolume();
    ApplyInput();
    ApplyLoudness();
}
