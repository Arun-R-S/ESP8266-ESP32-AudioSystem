#include "AudioDriverManager.h"
#include "TDA7439Driver.h"
#include "core/SettingsStruct.h"
#include "core/Logger.h"
#include <string.h>
#include "core/SettingsManager.h"

AudioDriverManager& AudioDriverManager::Instance() {
    static AudioDriverManager instance;
    return instance;
}

void AudioDriverManager::Init(I2CBus& bus) {
    AddLogDebug("AudioDriverManager", "Settings Active Audio Driver - %s",Settings.audio.activeDriver);
    // this->_responseManager.Clear();
    // this->_responseManager.Append("{\"audio\":{");
    // this->_responseManager.Append("\"volume\":%d,", Settings.audio.volume);
    // this->_responseManager.Append("\"input\":%d,", Settings.audio.input);
    // this->_responseManager.Append("\"loudness\":%s,", Settings.audio.loudness ? "true" : "false");
    // this->_responseManager.Append("\"activeDriver\":\"%s\"},", Settings.audio.activeDriver);

    // this->_responseManager.Append("\"system\":{\"deviceName\":\"%s\"},", Settings.system.deviceName);

    // this->_responseManager.Append("\"crc32\":\"0x%08X\"}", Settings.crc32);

    // AddLogInfo("AudioDriverManager", "JSON: %s", this->_responseManager.Get());
    if (strcmp(Settings.audio.activeDriver, "TDA7439") == 0) {
        AddLogDebug("AudioDriverManager", "Settings Active Audio Driver - 0x%02X",Settings.DeviceConfig.AudioIC.TDA7439_Address);
        activeDriver = new TDA7439Driver(bus, Settings.DeviceConfig.AudioIC.TDA7439_Address);
    }
    // (Future) else if (strcmp(Settings.audio.activeDriver, "PT2322") == 0) { ... }

    if (activeDriver != nullptr) {
        activeDriver->Init();
        AddLogInfo("AudioDriverManager", "Audio driver initialized");
    } else {
        AddLogError("AudioDriverManager", "No valid audio driver selected");
    }
}

IAudioDriver* AudioDriverManager::GetActiveDriver() {
    AddLogDebug("AudioDriverManager","GetActiveDrivers Start");
    return activeDriver;
}
