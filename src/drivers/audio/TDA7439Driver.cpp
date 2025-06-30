#include "TDA7439Driver.h"
#include "core/Logger.h"

TDA7439Driver::TDA7439Driver(I2CBus& bus) : _bus(&bus) {}

bool TDA7439Driver::Init() {
    if (!_bus->Detect(TDA7439_ADDRESS)) {
        AddLogError("AudioDriver_TDA7439", "[TDA7439] Device not found");
        return false;
    }
    AddLogInfo("AudioDriver_TDA7439", "[TDA7439] Initialized");
    return true;
}

bool TDA7439Driver::SetVolume(uint8_t value) {
    return WriteRegister(0x02, value);
}

bool TDA7439Driver::SetBass(int8_t value) {
    return WriteRegister(0x03, ConvertSoundValue(value));
}

bool TDA7439Driver::SetTreble(int8_t value) {
    return WriteRegister(0x05, ConvertSoundValue(value));
}

bool TDA7439Driver::SetBalance(int8_t value) {
    uint8_t left = (value < 0) ? 0 : value;
    uint8_t right = (value > 0) ? 0 : -value;
    WriteRegister(0x06, right);
    WriteRegister(0x07, left);
    return true;
}

bool TDA7439Driver::SetInput(uint8_t input) {
    return WriteRegister(0x00, input);
}

bool TDA7439Driver::Mute() {
    return WriteRegister(0x02, 0x38);
}

AudioFeature TDA7439Driver::GetSupportedFeatures() {
    return AudioFeature::Volume | AudioFeature::Bass | AudioFeature::Treble |
           AudioFeature::Balance | AudioFeature::Input | AudioFeature::Mute;
}

bool TDA7439Driver::WriteRegister(uint8_t reg, uint8_t data) {
    return _bus->Write(TDA7439_ADDRESS, reg, data);
}

uint8_t TDA7439Driver::ConvertSoundValue(int8_t val) {
    return (val < 0) ? (uint8_t)(-val) : 0;
}
