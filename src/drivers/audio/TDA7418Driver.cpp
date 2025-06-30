#include "TDA7418Driver.h"
#include "core/Logger.h"

TDA7418Driver::TDA7418Driver(I2CBus& bus) : _bus(&bus) {}

bool TDA7418Driver::Init() {
    if (!_bus->Detect(TDA7418_ADDRESS)) {
        AddLogError("AudioDriver_TDA7418", "[TDA7418] Device not found");
        return false;
    }
    AddLogInfo("AudioDriver_TDA7418", "[TDA7418] Initialized");
    return true;
}

bool TDA7418Driver::SetVolume(uint8_t value) {
    return WriteRegister(0x02, value);
}

bool TDA7418Driver::SetBass(int8_t value) {
    return WriteRegister(0x03, ConvertSoundValue(value));
}

bool TDA7418Driver::SetMiddle(int8_t value) {
    return WriteRegister(0x04, ConvertSoundValue(value));
}

bool TDA7418Driver::SetTreble(int8_t value) {
    return WriteRegister(0x05, ConvertSoundValue(value));
}

bool TDA7418Driver::SetBalance(int8_t value) {
    uint8_t left = (value < 0) ? 0 : value;
    uint8_t right = (value > 0) ? 0 : -value;
    WriteRegister(0x06, right);  // Right attenuation
    WriteRegister(0x07, left);   // Left attenuation
    return true;
}

bool TDA7418Driver::SetInput(uint8_t input) {
    return WriteRegister(0x00, input);
}

bool TDA7418Driver::Mute() {
    return WriteRegister(0x02, 0x38);  // Mute command
}

bool TDA7418Driver::EnableLoudness(bool enable) {
    uint8_t data = enable ? 0x01 : 0x00;
    return WriteRegister(0x09, data);
}

AudioFeature TDA7418Driver::GetSupportedFeatures() {
    return AudioFeature::Volume | AudioFeature::Bass | AudioFeature::Middle |
           AudioFeature::Treble | AudioFeature::Balance | AudioFeature::Input |
           AudioFeature::Mute | AudioFeature::Loudness | AudioFeature::Subwoofer;
}

bool TDA7418Driver::WriteRegister(uint8_t reg, uint8_t data) {
    return _bus->Write(TDA7418_ADDRESS, reg, data);
}

uint8_t TDA7418Driver::ConvertSoundValue(int8_t val) {
    return (val < 0) ? (uint8_t)(-val) : 0;
}
