#pragma once

#include <Arduino.h>

struct I2CConfig_t {
    uint8_t SDA;
    uint8_t SCL;
    uint8_t BusSpeed;  // Optional: 100 or 400 KHz
};

struct AudioICConfig_t {
    uint8_t TDA7439_Address;
    uint8_t PT2322_Address;
};

struct PinConfig_t {
    uint8_t Button1;
    uint8_t Button2;
    uint8_t Relay1;
    uint8_t LED;
};

struct DeviceConfig_t {
    I2CConfig_t I2C;
    AudioICConfig_t AudioIC;
    PinConfig_t Pins;
    bool EnableLoudness;
    bool EnableDisplay;
    bool EnableWebUI;
};

const DeviceConfig_t DefaultDeviceConfig = {
    .I2C = {
        .SDA = 4,
        .SCL = 5,
        .BusSpeed = 100  // 100KHz
    },
    .AudioIC = {
        .TDA7439_Address = 0x44,
        .PT2322_Address = 0x46
    },
    .Pins = {
        .Button1 = 12,
        .Button2 = 14,
        .Relay1  = 15,
        .LED     = 2
    },
    .EnableLoudness = true,
    .EnableDisplay  = true,
    .EnableWebUI    = true
};
