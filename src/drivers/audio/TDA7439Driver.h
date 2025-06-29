#pragma once

#include "IAudioDriver.h"
#include "hal/I2CBus.h"
#include "core/Logger.h"
#include "core/StatusManager.h"

// ==========================
// TDA7439 Constants & Macros
// ==========================
#define TDA7439_I2C_ADDRESS   0x44

// Register Map
#define REG_INPUT_SEL         0x00
#define REG_INPUT_GAIN        0x01
#define REG_VOLUME            0x02
#define REG_BASS              0x03
#define REG_MIDDLE            0x04
#define REG_TREBLE            0x05
#define REG_R_ATTENUATION     0x06
#define REG_L_ATTENUATION     0x07

// Input Selection Values
#define INPUT_1               0x03
#define INPUT_2               0x02
#define INPUT_3               0x01
#define INPUT_4               0x00

// Special Values
#define VOLUME_MUTE           0x38

#define TDA7439_ADDRESS 0x44

class TDA7439Driver : public IAudioDriver {
public:
    TDA7439Driver(I2CBus& bus);
    bool Init() override;
    const char* GetDriverName() override { return "TDA7439"; }

    bool SetVolume(uint8_t value) override;
    bool SetInput(uint8_t input) override;
    bool SetBass(int8_t value) override;
    bool SetTreble(int8_t value) override;
    bool SetBalance(int8_t value) override;
    bool Mute() override;

    bool SupportsFeature(AudioFeature feature) override;

private:
    I2CBus* _bus;

    bool WriteRegister(uint8_t reg, uint8_t data);
    uint8_t ConvertSoundValue(int8_t val);
};
