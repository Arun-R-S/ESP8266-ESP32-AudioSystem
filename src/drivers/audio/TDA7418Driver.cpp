#include "TDA7418Driver.h"

// Register map
#define REG_SOURCE_SEL   0x00
#define REG_LOUDNESS     0x01
#define REG_VOLUME       0x02
#define REG_TREBLE       0x03
#define REG_MIDDLE       0x04
#define REG_BASS         0x05
#define REG_MID_BAS_FC   0x06
#define REG_SPK_ATT_FL   0x07
#define REG_SPK_ATT_RL   0x08
#define REG_SPK_ATT_RR   0x09
#define REG_SPK_ATT_FR   0x0A
#define REG_SPK_ATT_SUB  0x0B
#define REG_SOFTMUTE     0x0C
#define REG_AUDIO_TEST   0x0D

TDA7418Driver::TDA7418Driver(I2CBus* bus, uint8_t address)
    : _bus(bus), _address(address) {
    resetRegisters();
}

void TDA7418Driver::resetRegisters() {
    for (int i = 0; i < 14; i++) {
        _registers[i] = 0xFE;  // Default power-on value
    }
}

bool TDA7418Driver::begin() {
    resetRegisters();
    if (!batchWrite(REG_SOURCE_SEL, _registers, 14)) {
        AddLogError("AudioDriver_TDA7418","Initialization failed");
        StatusManager::SetError("AudioDriver_TDA7418", ErrorCode::ERROR_I2C_WRITE_FAILED);
        return false;
    }
    AddLogInfo("AudioDriver_TDA7418","Initialized successfully");
    return true;
}

bool TDA7418Driver::SetVolume(int volume) {
    _registers[REG_VOLUME] = volumeToRegister(volume);
    return writeRegister(REG_VOLUME, _registers[REG_VOLUME]);
}

bool TDA7418Driver::SetInput(uint8_t input) {
    _registers[REG_SOURCE_SEL] &= 0xF8;  // Clear input bits
    _registers[REG_SOURCE_SEL] |= (input & 0x07);
    return writeRegister(REG_SOURCE_SEL, _registers[REG_SOURCE_SEL]);
}

bool TDA7418Driver::SetTone(int bass, int middle, int treble) {
    _registers[REG_BASS] = attenuationToRegister(bass);
    _registers[REG_MIDDLE] = attenuationToRegister(middle);
    _registers[REG_TREBLE] = attenuationToRegister(treble);

    return writeRegister(REG_BASS, _registers[REG_BASS]) &&
           writeRegister(REG_MIDDLE, _registers[REG_MIDDLE]) &&
           writeRegister(REG_TREBLE, _registers[REG_TREBLE]);
}

bool TDA7418Driver::SetLoudness(bool enable, uint8_t attenuation) {
    if (enable) {
        _registers[REG_LOUDNESS] = (attenuation & 0x0F);
    } else {
        _registers[REG_LOUDNESS] = 0x00;
    }
    return writeRegister(REG_LOUDNESS, _registers[REG_LOUDNESS]);
}

bool TDA7418Driver::SetSpeakerLevels(int fl, int fr, int rl, int rr, int sub) {
    _registers[REG_SPK_ATT_FL] = attenuationToRegister(fl);
    _registers[REG_SPK_ATT_FR] = attenuationToRegister(fr);
    _registers[REG_SPK_ATT_RL] = attenuationToRegister(rl);
    _registers[REG_SPK_ATT_RR] = attenuationToRegister(rr);
    _registers[REG_SPK_ATT_SUB] = attenuationToRegister(sub);

    return batchWrite(REG_SPK_ATT_FL, &_registers[REG_SPK_ATT_FL], 5);
}

bool TDA7418Driver::writeRegister(uint8_t reg, uint8_t value) {
    if (!_bus->Write(_address, reg, value)) {
        AddLogError("AudioDriver_TDA7418","I2C write failed (Reg 0x%02X)", reg);
        StatusManager::SetError("AudioDriver_TDA7418", ErrorCode::ERROR_I2C_WRITE_FAILED);
        return false;
    }
    return true;
}

// bool TDA7418Driver::batchWrite(uint8_t startReg, uint8_t* data, uint8_t length) {
//     if (!_bus->Write(_address, startReg, data, length)) {
//         AddLogError("AudioDriver_TDA7418","I2C batch write failed (StartReg 0x%02X)", startReg);
//         StatusManager::SetError("AudioDriver_TDA7418", ErrorCode::ERROR_I2C_WRITE_FAILED);
//         return false;
//     }
//     return true;
// }

bool TDA7418Driver::batchWrite(uint8_t startReg, uint8_t* data, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        if (!writeRegister(startReg + i, data[i])) {
            return false;
        }
    }
    return true;
}

uint8_t TDA7418Driver::volumeToRegister(int value) {
    value = constrain(value, -80, 15);
    if (value >= 0) return value;
    return 16 + abs(value);
}

uint8_t TDA7418Driver::attenuationToRegister(int value) {
    value = constrain(value, -15, 15);
    if (value >= 0) return 15 - value;
    return 15 + abs(value);
}
