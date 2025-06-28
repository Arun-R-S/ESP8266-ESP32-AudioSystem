#include "AudioCommands.h"
#include "core/Logger.h"
#include "services/AudioService.h"

AudioService audioService;

bool CmdAudioSetVolume(const String& payload) {
    if (!payload.isEmpty())
    {
        int vol = payload.toInt();
        AddLogInfo("Audio", "Setting volume to %d", vol);
        audioService.SetVolume(vol);
        return true;
    }
    else
    {
        AddLogWarn("Audio", "No payload provided");
        return false;
    }
    return false;
}

void RegisterAudioCommands(CommandRegistry& registry) {
    registry.Register("SetVolume", CmdAudioSetVolume);
}
