#include "App.h"
#include "Logger.h"
#include "../hal/I2CBus.h"
#include "boards/Board_Definitions.h"
#include "core/CommandRegistry.h"
#include "core/CommandProcessor.h"
#include "handlers/I2CCommands.h"
#include "handlers/AudioCommands.h"
#include "handlers/SystemCommands.h"
#include "handlers/SettingsCommands.h"
#include "config/SettingsManager.h"
#include "ResponseManager.h"
#include "core/WifiManager.h"
#include "ui/WebServerManager.h"
#include <ESPAsyncWebServer.h>

//TDA7439Driver audio(i2c, 0x44);

CommandRegistry registry;
CommandProcessor processor(registry);

ResponseManager responseManger;

WiFiManager _wifiManager;

AsyncWebServer serve(80);

void App::Setup() {
    // Initialization code
    Serial.begin(115200);
    // Initialize Logger
    Logger::Begin(Serial, LOG_LEVEL_DEBUG);
    AddLog("App", "Starting Audio Controller");
    delay(300);
    
    SettingsManager::Instance().LoadSettings();
    delay(1000);
    _wifiManager.begin();
    I2CBus i2c(BOARD_PIN_SDA, BOARD_PIN_SCL);
    i2c.Init();

    WebServerManager::Begin(serve);
    //AudioDriverManager::Instance().Init(i2c);
    // Register command sets
    RegisterI2CCommands(registry);
    RegisterAudioCommands(registry);
    RegisterSystemCommands(registry);
    RegisterSettingsCommands(registry);
}

void App::Loop() {
    // Future: handle UI, web server, button presses
    // Loop code
    //AddLog("App", "App running...");
    processor.ProcessSerial();
    _wifiManager.handle();
}
