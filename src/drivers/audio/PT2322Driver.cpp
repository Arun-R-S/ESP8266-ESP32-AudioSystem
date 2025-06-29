#include "PT2322Driver.h"
#include "core/Logger.h"
#include "core/StatusManager.h"

PT2322Driver::PT2322Driver(I2CBus& bus) : _bus(&bus) {}

bool PT2322Driver::Init() {
    AddLogInfo("AudioDriver_PT2322", "Initializing...");

    if (!WriteRegister(PT2322_SYSTEM_RESET, 0)) {
        AddLogError("AudioDriver_PT2322", "Device not found at 0x44");
        StatusManager::SetError("AudioDriver_PT2322", ERROR_DEVICE_NOT_FOUND);
        return false;
    }

    WriteRegister(PT2322_INPUT_SWITCH, 0);

    // Initialize channels to 0dB
    WriteRegister(PT2322_FL_VOLUME, 0);
    WriteRegister(PT2322_FR_VOLUME, 0);
    WriteRegister(PT2322_CENTER_VOLUME, 0);
    WriteRegister(PT2322_RL_VOLUME, 0);
    WriteRegister(PT2322_RR_VOLUME, 0);
    WriteRegister(PT2322_SUB_VOLUME, 0);

    WriteMasterVolume(0);
    WriteRegister(PT2322_FUNCTION_SELECT, _functionState);

    AddLogInfo("AudioDriver_PT2322", "Initialized successfully.");
    return true;
}

bool PT2322Driver::SetVolume(uint8_t value) {
    return WriteMasterVolume(value);
}

bool PT2322Driver::SetInput(uint8_t input) {
    AddLogWarn("AudioDriver_PT2322", "SetInput not supported.");
    return false;
}

bool PT2322Driver::SetBass(int8_t value) {
    return WriteRegister(PT2322_BASS_CONTROL, ConvertTone(value));
}

bool PT2322Driver::SetTreble(int8_t value) {
    return WriteRegister(PT2322_TREBLE_CONTROL, ConvertTone(value));
}

bool PT2322Driver::SetBalance(int8_t value) {
    // Balance by adjusting left/right channels
    uint8_t left = (value < 0) ? 0 : value;
    uint8_t right = (value > 0) ? 0 : -value;
    bool res = WriteRegister(PT2322_FL_VOLUME, left) &&
               WriteRegister(PT2322_FR_VOLUME, right);
    return res;
}

bool PT2322Driver::Mute() {
    _functionState |= PT2322_MUTE_BIT;
    return WriteRegister(PT2322_FUNCTION_SELECT, _functionState);
}

bool PT2322Driver::SupportsFeature(AudioFeature feature) {
    switch (feature) {
        case AudioFeature::Volume:
        case AudioFeature::Bass:
        case AudioFeature::Treble:
        case AudioFeature::Balance:
        case AudioFeature::FrontLeft:
        case AudioFeature::FrontRight:
        case AudioFeature::Center:
        case AudioFeature::RearLeft:
        case AudioFeature::RearRight:
        case AudioFeature::Subwoofer:
            return true;
        case AudioFeature::Input:
        default:
            return false;
    }
}

bool PT2322Driver::WriteRegister(uint8_t reg, uint8_t data) {
    if (!_bus) return false;
    bool success = _bus->Write(PT2322_ADDRESS, reg , data);
    if (!success) {
        AddLogError("AudioDriver_PT2322", "I2C Write failed: Reg 0x%02X Data 0x%02X", reg, data);
        StatusManager::SetError("AudioDriver_PT2322", ERROR_I2C_WRITE_FAILED);
    }
    return success;
}

bool PT2322Driver::WriteMasterVolume(uint8_t volume) {
    uint8_t vol = (volume > 79) ? 79 : volume;
    uint8_t tens = vol / 10;
    uint8_t ones = vol % 10;
    bool success = _bus->Write(PT2322_ADDRESS, PT2322_MASTER_VOL_1STEP , ones) &&
                   _bus->Write(PT2322_ADDRESS, PT2322_MASTER_VOL_10STEP , tens);
    if (!success) {
        AddLogError("AudioDriver_PT2322", "Master Volume Write failed.");
        StatusManager::SetError("AudioDriver_PT2322", ERROR_I2C_WRITE_FAILED);
    }
    return success;
}

uint8_t PT2322Driver::ConvertTone(int8_t val) {
    if (val < -14) val = -14;
    if (val > 14) val = 14;
    return (val < 0) ? (7 + abs(val)) : (7 - val);
}
