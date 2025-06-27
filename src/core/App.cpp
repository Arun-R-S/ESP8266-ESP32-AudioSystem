#include "App.h"
#include "Logger.h"
#include "../hal/I2CBus.h"
#include "../drivers/audio/TDA7439Driver.h"
#include "boards/BoardConfig.h"

I2CBus i2c(DEFAULT_SDA, DEFAULT_SCL);
TDA7439Driver audio(i2c, 0x44);

void App::Setup() {
    // Initialization code
    Serial.begin(115200);
    Serial.println("App setup complete");
    Logger::Init();
    Logger::Info("System", "Starting Audio Controller");

    i2c.Init();
    audio.Init();

    audio.SetVolume(10);
    audio.SetInput(1);
    audio.SetLoudness(true);
}

void App::Loop() {
    // Future: handle UI, web server, button presses
    // Loop code
    Serial.println("App running...");
    Logger::Info("System", "App running...");
    delay(1000);
}
