#pragma once

#include "IAudioDriver.h"
#include "hal/I2CBus.h"
#include "core/StatusManager.h"

// =======================
// PT2322 I2C Address
// =======================
#define PT2322_ADDRESS 0x44

// =======================
// Register Definitions
// =======================
#define PT2322_FL_VOLUME         0x10
#define PT2322_FR_VOLUME         0x20
#define PT2322_CENTER_VOLUME     0x30
#define PT2322_RL_VOLUME         0x40
#define PT2322_RR_VOLUME         0x50
#define PT2322_SUB_VOLUME        0x60
#define PT2322_FUNCTION_SELECT   0x70
#define PT2322_BASS_CONTROL      0x90
#define PT2322_MIDDLE_CONTROL    0xA0
#define PT2322_TREBLE_CONTROL    0xB0
#define PT2322_INPUT_SWITCH      0xC7
#define PT2322_MASTER_VOL_1STEP  0xD0
#define PT2322_MASTER_VOL_10STEP 0xE0
#define PT2322_SYSTEM_RESET      0xFF

// Function Bits
#define PT2322_MUTE_BIT          0x08
#define PT2322_3D_BIT            0x04
#define PT2322_TONE_OFF_BIT      0x02


class PT2322Driver : public IAudioDriver {
public:
    explicit PT2322Driver(I2CBus& bus);

    bool Init() override;
    const char* GetDriverName() override { return "PT2322"; }

    bool SetVolume(uint8_t value) override;
    bool SetInput(uint8_t input) override;
    bool SetBass(int8_t value) override;
    bool SetTreble(int8_t value) override;
    bool SetBalance(int8_t value) override;
    bool Mute() override;

    bool SupportsFeature(AudioFeature feature) override;

private:
    I2CBus* _bus;
    uint8_t _functionState = PT2322_3D_BIT;

    bool WriteRegister(uint8_t reg, uint8_t data);
    bool WriteMasterVolume(uint8_t volume);
    uint8_t ConvertTone(int8_t value);
};
