#include "AudioDriver.h"
//#include "drivers/audio/TDA7439Driver.h"
//#include "drivers/audio/PT2322Driver.h"
#include "core/SettingsManager.h"
#include "core/Logger.h"

AudioDriver* AudioManager::_driver = nullptr;

void AudioDriverManager::Init(I2CBus& bus) {
    String driver = Settings.audio.activeDriver;

    if (driver == "TDA7439") {
        _driver = new TDA7439Driver(bus);
    } else if (driver == "PT2322") {
        _driver = new PT2322Driver(bus);
    } else {
        AddLogError("AudioDriverManager", "Unknown driver: %s", driver.c_str());
        _driver = nullptr;
    }

    if (_driver) {
        _driver->Init();
        AddLogInfo("AudioDriverManager", "Loaded driver: %s", _driver->GetDriverName());
    }
}

AudioDriver* AudioDriverManager::GetDriver() {
    return _driver;
}

const char* AudioDriverManager::GetCurrentDriverName() {
    return _driver ? _driver->GetDriverName() : "None";
}
