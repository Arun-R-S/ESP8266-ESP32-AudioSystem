#include "IAudioDriver.h"
#include "drivers/audio/TDA7439Driver.h"
//#include "drivers/audio/PT2322Driver.h"
#include "AudioDriverManager.h"
#include "core/SettingsManager.h"
#include "core/Logger.h"
#include "core/StatusManager.h"

IAudioDriver* AudioDriverManager::_driver = nullptr;

void AudioDriverManager::Init(I2CBus& bus) {
    if (_driver) {
        delete _driver;
        _driver = nullptr;
    }
    String driver = Settings.audio.activeDriver;

    if (driver == "TDA7439") {
        _driver = new TDA7439Driver(bus);
    } 
    //else if (driver == "PT2322") {
    //     _driver = new PT2322Driver(bus);
    // } 
    else {
        AddLogError("AudioDriverManager", "Unknown driver: %s", driver.c_str());
        _driver = nullptr;
    }

    if (_driver) {
        if (!_driver->Init())
        {
            StatusManager::SetError("AudioDriverManager", ERROR_DRIVER_INIT_FAILED);
        }
        AddLogInfo("AudioDriverManager", "Loaded driver: %s", _driver->GetDriverName());
    }
}

IAudioDriver* AudioDriverManager::GetDriver() {
    return _driver;
}

const char* AudioDriverManager::GetCurrentDriverName() {
    return _driver ? _driver->GetDriverName() : "None";
}

const char* AudioDriverManager::GetActiveDriver() {
    return _driver ? _driver->GetDriverName() : "None";
}
