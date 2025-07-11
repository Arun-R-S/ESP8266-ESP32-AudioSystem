#include "AudioCommands.h"
#include "core/Logger.h"
#include "services/AudioService.h"

AudioService audioService;

bool CmdAudioSetVolume(const String& payload) {
    if (!payload.isEmpty())
    {
        uint8_t vol = payload.toInt();
        AddLogInfo("CmdAudio", "Setting volume to %d", vol);
        audioService.SetVolume(vol);
        return true;
    }
    else
    {
        AddLogWarn("CmdAudio", "No payload provided");
        return false;
    }
    return false;
}

void RegisterAudioCommands(CommandRegistry& registry) {
    registry.Register("SetVolume", CmdAudioSetVolume);
}
