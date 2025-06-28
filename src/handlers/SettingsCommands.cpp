#include "I2CCommands.h"
#include "core/Logger.h"
#include "Wire.h"
#include "core/SettingsManager.h"

bool CmdSettings(const String &payload)
{
    if (!payload.isEmpty())
    {
        String cmd = payload;
        cmd.toLowerCase();
        AddLogDebug("CmdSettings", "Payload is %s", cmd.c_str());
        if(cmd == "all")
        {
            AddLogDebug("CmdSettings", "Full Settings");
            SettingsManager::Instance().GetSettings();
            return true;
        }
        else{
            AddLogDebug("CmdSettings", "Command Not Found");
            return false;
        }
    }
    else
    {
        AddLogWarn("CmdSettings", "No payload provided");
        return false;
    }
    return false;
}

void RegisterSettingsCommands(CommandRegistry &registry)
{
    registry.Register("Settings", CmdSettings);
}
