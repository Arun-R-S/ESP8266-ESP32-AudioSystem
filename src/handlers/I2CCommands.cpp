#include "I2CCommands.h"
#include "core/Logger.h"
#include "Wire.h"
#include "hal/I2CBus.h"

bool CmdI2C(const String &payload)
{
    if (!payload.isEmpty())
    {
        String cmd = payload;
        cmd.toLowerCase();
        AddLogDebug("CmdI2C", "Payload is %s", cmd.c_str());
        if(cmd == "scan")
        {
            AddLogInfo("CmdI2C", "Scan Initiated");
            I2CBus::Scan();
            return true;
        }
        else{
            AddLogDebug("CmdI2C", "Command Not Found");
            return false;
        }
    }
    else
    {
        AddLogWarn("CmdI2C", "No payload provided");
        return false;
    }
    return false;
}

void RegisterI2CCommands(CommandRegistry &registry)
{
    registry.Register("I2C", CmdI2C);
}
