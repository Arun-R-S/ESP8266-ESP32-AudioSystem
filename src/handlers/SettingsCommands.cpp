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
        else if(cmd == "resetdefault")
        {
            AddLogDebug("CmdSettings", "Reset Default Command");
            SettingsManager::Instance().ResetSettingsToDefault();
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

bool CmdSettingsLogger(const String &payload)
{
    if (!payload.isEmpty())
    {
        String cmd = payload;
        cmd.toLowerCase();
        AddLogDebug("CmdSettingsLogger", "Payload is %s", cmd.c_str());
        if(cmd == "loglevel1")
        {
            AddLog("CmdSettingsLogger", "Setting Loglevel 1");
            Settings.logger.CurrentLogLevel = LOG_LEVEL_INFO;
            SetLoggerLevel(Settings.logger.CurrentLogLevel);
            return true;
        }
        else if(cmd == "loglevel2")
        {
            AddLog("CmdSettingsLogger", "Setting Loglevel 2");
            Settings.logger.CurrentLogLevel = LOG_LEVEL_WARN;
            SetLoggerLevel(Settings.logger.CurrentLogLevel);
            return true;
        }
        else if(cmd == "loglevel3")
        {
            AddLog("CmdSettingsLogger", "Setting Loglevel 3");
            Settings.logger.CurrentLogLevel = LOG_LEVEL_ERROR;
            SetLoggerLevel(Settings.logger.CurrentLogLevel);
            return true;
        }
        else if(cmd == "loglevel7")
        {
            AddLog("CmdSettingsLogger", "Setting Loglevel 7");
            Settings.logger.CurrentLogLevel = LOG_LEVEL_CORE;
            SetLoggerLevel(Settings.logger.CurrentLogLevel);
            return true;
        }
        else{
            AddLogDebug("CmdSettingsLogger", "Command Not Found");
            return false;
        }
    }
    else
    {
        AddLogWarn("CmdSettingsLogger", "No payload provided");
        return false;
    }
    return false;
}

void RegisterSettingsCommands(CommandRegistry &registry)
{
    registry.Register("Settings", CmdSettings);
    registry.Register("SettingsLogger", CmdSettingsLogger);
}
