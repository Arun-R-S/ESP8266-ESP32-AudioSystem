#include "AudioCommands.h"
#include "core/Logger.h"

bool CmdAudioSetVolume(const String& payload) {
    int vol = payload.toInt();
    AddLogInfo("Audio", "Setting volume to %d", vol);
    // AudioDriver.SetVolume(vol);   <-- Implement this
    return true;
}

void RegisterAudioCommands(CommandRegistry& registry) {
    registry.Register("SetVolume", CmdAudioSetVolume);
}
