#include "App.h"
#include "Logger.h"
#include "../hal/I2CBus.h"
#include "../drivers/audio/TDA7439Driver.h"
#include "boards/BoardConfig.h"
#include <GDBStub.h>

I2CBus i2c(DEFAULT_SDA, DEFAULT_SCL);
TDA7439Driver audio(i2c, 0x44);

void App::Setup() {
    // Initialization code
    Serial.begin(115200);
    AddLog("App", "Starting Audio Controller");
    gdbstub_init();
    i2c.Init();
    audio.Init();   

    audio.SetVolume(10);
    audio.SetInput(1);
    audio.SetLoudness(true);
}

void App::Loop() {
    // Future: handle UI, web server, button presses
    // Loop code
    AddLog("App", "App running...");
    delay(1000);
}
