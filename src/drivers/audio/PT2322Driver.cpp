#include "PT2322Driver.h"
#include "core/Logger.h"

PT2322Driver::PT2322Driver(I2CBus& bus) : _bus(&bus) {}

bool PT2322Driver::Init() {
    if (!_bus->Detect(PT2322_ADDRESS)) {
        AddLogError("AudioDriver_PT2322", "[PT2322] Device not found");
        return false;
    }
    AddLogInfo("AudioDriver_PT2322", "[PT2322] Initialized");
    return true;
}

bool PT2322Driver::SetVolume(uint8_t value) {
    return WriteRegister(0x00, value);
}

bool PT2322Driver::SetInput(uint8_t input) {
    return WriteRegister(0x01, input);
}

AudioFeature PT2322Driver::GetSupportedFeatures() {
    return AudioFeature::Volume | AudioFeature::Input |
           AudioFeature::FrontLeft | AudioFeature::FrontRight |
           AudioFeature::RearLeft | AudioFeature::RearRight |
           AudioFeature::Center;
}

bool PT2322Driver::SupportsFeature(AudioFeature feature) {
    return hasFeature(GetSupportedFeatures(), feature);
}

bool PT2322Driver::WriteRegister(uint8_t reg, uint8_t data) {
    return _bus->Write(PT2322_ADDRESS, reg, data);
}
