#include "Logger.h"
#include "../hal/I2CBus.h"
#include "../drivers/audio/TDA7439Driver.h"
#include "/config/Config.h"

I2CBus i2c(DEFAULT_SDA, DEFAULT_SCL);
TDA7439Driver audio(i2c, 0x44);

void setup() {
    Logger::Init();
    Logger::Info("System", "Starting Audio Controller");

    i2c.Init();
    audio.Init();

    audio.SetVolume(10);
    audio.SetInput(1);
    audio.SetLoudness(true);
}

void loop() {
    // Future: handle UI, web server, button presses
}
