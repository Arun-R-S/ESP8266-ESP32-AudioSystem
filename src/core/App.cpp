#include "App.h"
#include "Logger.h"
#include "../hal/I2CBus.h"
#include "../drivers/audio/TDA7439Driver.h"
#include "boards/BoardConfig.h"
#include "core/CommandRegistry.h"
#include "core/CommandProcessor.h"
#include "handlers/I2CCommands.h"
#include "handlers/AudioCommands.h"
#include "SettingsManager.h"
#include "ResponseManager.h"

I2CBus i2c(DEFAULT_SDA, DEFAULT_SCL);
TDA7439Driver audio(i2c, 0x44);

CommandRegistry registry;
CommandProcessor processor(registry);

ResponseManager responseManger;

void App::Setup() {
    // Initialization code
    Serial.begin(115200);
    AddLog("App", "Starting Audio Controller");
    delay(300);
    SettingsManager::Instance().LoadSettings();
    responseManger.Clear();
    responseManger.Append("{\"audio\":{");
    responseManger.Append("\"volume\":%d,", Settings.audio.volume);
    responseManger.Append("\"input\":%d,", Settings.audio.input);
    responseManger.Append("\"loudness\":%s,", Settings.audio.loudness ? "true" : "false");
    responseManger.Append("\"activeDriver\":\"%s\"},", Settings.audio.activeDriver);

    responseManger.Append("\"system\":{\"deviceName\":\"%s\"},", Settings.system.deviceName);

    responseManger.Append("\"crc32\":\"0x%08X\"}", Settings.crc32);

    AddLogInfo("Settings", "JSON: %s", responseManger.Get());
    i2c.Init();
    audio.Init();   

    audio.SetVolume(10);
    audio.SetInput(1);
    audio.SetLoudness(true);

    // Register command sets
    RegisterI2CCommands(registry);
    RegisterAudioCommands(registry);
}

void App::Loop() {
    // Future: handle UI, web server, button presses
    // Loop code
    //AddLog("App", "App running...");
    processor.ProcessSerial();
}
