#include "SystemCommands.h"
#include "core/Logger.h"

bool CmdReboot(const String &payload)
{
    #if defined(ESP8266)
        ESP.restart();
    #elif defined(ESP32)
        ESP.restart();
    #endif

    return true;
}

bool CmdReset(const String &payload)
{
    #if defined(ESP8266)
        ESP.reset();
    #elif defined(ESP32)
        esp_restart();
    #endif

    return true;
}


void RegisterSystemCommands(CommandRegistry &registry)
{
    registry.Register("REBOOT", CmdReboot);
    registry.Register("RESTART", CmdReboot);
    registry.Register("RESET", CmdReset);
}
