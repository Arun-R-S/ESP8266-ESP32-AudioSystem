#include "AudioCommands.h"
#include "core/Logger.h"
#include "drivers/audio/AudioDriver.h"

bool CmdAudioSetVolume(const String& payload) {
    if (!payload.isEmpty())
    {
        int vol = payload.toInt();
        AddLogInfo("Audio", "Setting volume to %d", vol);
        //AudioDriver::SetVolume();   
        return true;
    }
    else
    {
        AddLogWarn("CmdI2C", "No payload provided");
        return false;
    }
    return false;
}

void RegisterAudioCommands(CommandRegistry& registry) {
    registry.Register("SetVolume", CmdAudioSetVolume);
}
