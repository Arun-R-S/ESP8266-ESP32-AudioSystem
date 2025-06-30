#pragma once

#include "AudioFeature.h"
#include "core/Logger.h"

class IAudioDriver {
public:
    virtual const char* GetDriverName() = 0;
    virtual bool Init() = 0;

    virtual bool SetVolume(uint8_t value) { LogFunctionNotAvailable("SetVolume"); return false; }
    virtual bool SetInput(uint8_t input) { LogFunctionNotAvailable("SetInput"); return false; }
    virtual bool SetBass(int8_t value) { LogFunctionNotAvailable("SetBass"); return false; }
    virtual bool SetTreble(int8_t value) { LogFunctionNotAvailable("SetTreble"); return false; }
    virtual bool SetBalance(int8_t value) { LogFunctionNotAvailable("SetBalance"); return false; }
    virtual bool Mute() { LogFunctionNotAvailable("Mute"); return false; }

    virtual AudioFeature GetSupportedFeatures() { return AudioFeature::None; }

    virtual bool SupportsFeature(AudioFeature feature) {
        return hasFeature(GetSupportedFeatures(), feature);
    }

protected:
    void LogFunctionNotAvailable(const char* function) {
        AddLogError("IAudioDriver", "[%s] Function '%s' not available", GetDriverName(), function);
    }
};
