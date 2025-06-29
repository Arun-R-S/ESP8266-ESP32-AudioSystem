#include "TDA7439Driver.h"
#include "core/Logger.h"
#include "core/StatusManager.h"

// Constructor
TDA7439Driver::TDA7439Driver(I2CBus& bus) : _bus(&bus) {}

// Init
bool TDA7439Driver::Init() {
    AddLogInfo("AudioDriver_TDA7439", "Initializing...");
    if (!_bus->Detect(TDA7439_ADDRESS)) {
        AddLogError("AudioDriver_TDA7439", "Device not found at 0x%02X", TDA7439_ADDRESS);
        StatusManager::SetError("AudioDriver_TDA7439", ERROR_DEVICE_NOT_FOUND);
        return false;
    }
    AddLogInfo("AudioDriver_TDA7439", "Device found.");
    return true;
}

// Volume
bool TDA7439Driver::SetVolume(uint8_t value) {
    if (value == 0) {
        return WriteRegister(0x02, 0x38); // mute
    }
    uint8_t vol = 48 - value;
    return WriteRegister(0x02, vol);
}

// Input
bool TDA7439Driver::SetInput(uint8_t input) {
    uint8_t inputSel = (input >= 1 && input <= 4) ? (4 - input) : 0;
    return WriteRegister(0x00, inputSel);
}

// Bass
bool TDA7439Driver::SetBass(int8_t value) {
    return WriteRegister(0x03, ConvertSoundValue(value));
}

// Treble
bool TDA7439Driver::SetTreble(int8_t value) {
    return WriteRegister(0x05, ConvertSoundValue(value));
}

// Balance
bool TDA7439Driver::SetBalance(int8_t value) {
    uint8_t att = (value >= 0) ? value : -value;
    WriteRegister(0x06, att);  // Right attenuation
    WriteRegister(0x07, att);  // Left attenuation
    return true;
}

// Mute
bool TDA7439Driver::Mute() {
    return WriteRegister(0x02, 0x38);
}

// SupportsFeature
bool TDA7439Driver::SupportsFeature(AudioFeature feature) {
    switch (feature) {
        case AudioFeature::Volume:
        case AudioFeature::Input:
        case AudioFeature::Bass:
        case AudioFeature::Treble:
        case AudioFeature::Balance:
            return true;
        default:
            return false;
    }
}

// WriteRegister
bool TDA7439Driver::WriteRegister(uint8_t reg, uint8_t data) {
    bool success = _bus->Write(TDA7439_ADDRESS, reg, data);
    if (!success) {
        AddLogError("AudioDriver_TDA7439", "Failed to write Reg: 0x%02X, Data: 0x%02X", reg, data);
        StatusManager::SetError("AudioDriver_TDA7439", ERROR_DEVICE_NOT_FOUND);
    }
    return success;
}

// ConvertSoundValue
uint8_t TDA7439Driver::ConvertSoundValue(int8_t val) {
    if (val < -7) val = -7;
    if (val > 7) val = 7;
    return (val >= 0) ? (15 - val) : (7 + (-val));
}
