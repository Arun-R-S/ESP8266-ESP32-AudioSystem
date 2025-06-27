#include "TDA7439Driver.h"
#include "../../core/Logger.h"

TDA7439Driver::TDA7439Driver(I2CBus& bus, uint8_t address) : _i2c(bus), _address(address) {}

bool TDA7439Driver::Init() {
    //Logger::Info("Audio", "TDA7439 initialized at address 0x%02X", _address);
    Logger::Info("Audio", "TDA7439 initialized at address 0x%02X", _i2cAddress); 
    return true;
}

void TDA7439Driver::SetVolume(int level) {
    uint8_t val = constrain(31 - level, 0, 31);
    WriteRegister(0x00, val);
    Logger::Info("Audio", "Volume set to %d", level);
}

void TDA7439Driver::SetInput(uint8_t input) {
    WriteRegister(0x01, input & 0x03);
}

void TDA7439Driver::SetLoudness(bool enable) {
    WriteRegister(0x02, enable ? 0x10 : 0x00);
}

void TDA7439Driver::SetBass(int level) {
    WriteRegister(0x03, level & 0x0F);
}

void TDA7439Driver::SetTreble(int level) {
    WriteRegister(0x04, level & 0x0F);
}

void TDA7439Driver::SaveState() {
    // Use EEPROM or FlashStorage
}

void TDA7439Driver::LoadState() {
    // Load previous settings
}

uint8_t TDA7439Driver::getAddress() {
    return _i2cAddress;
}

void TDA7439Driver::WriteRegister(uint8_t reg, uint8_t value) {
    _i2c.Write(_address, reg, value);
}
