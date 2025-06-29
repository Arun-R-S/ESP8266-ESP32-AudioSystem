#include "TDA7418Driver.h"
#include "core/Logger.h"
#include "core/StatusManager.h"

// ==============================
// Constants
// ==============================
#define TDA7418_ADDRESS_DEFAULT 0x44
#define MAX_I2C_RETRIES 3

#define REG_SOURCE_SEL  0x00
#define REG_LOUDNESS    0x01
#define REG_VOLUME      0x02
#define REG_TREBLE      0x03
#define REG_MIDDLE      0x04
#define REG_BASS        0x05
#define REG_MID_BAS_FC  0x06
#define REG_SPK_ATT_FL  0x07
#define REG_SPK_ATT_RL  0x08
#define REG_SPK_ATT_RR  0x09
#define REG_SPK_ATT_FR  0x0A
#define REG_SPK_ATT_SUB 0x0B
#define REG_SOFTMUTE    0x0C
#define REG_AUDIO_TEST  0x0D
#define AUTOINCREMENT   0x20

// ==============================
// Constructor
// ==============================
TDA7418Driver::TDA7418Driver(TwoWire& wire, uint8_t i2cAddress)
    : _wire(&wire), _i2cAddress(i2cAddress) {}

// ==============================
// Initialization
// ==============================
bool TDA7418Driver::begin() {
    AddLogInfo("TDA7418", "Initializing...");

    for (uint8_t reg = REG_SOURCE_SEL; reg <= REG_AUDIO_TEST; reg++) {
        _registerData[reg] = 0xFE;
    }

    return batchWrite(REG_SOURCE_SEL, _registerData, 14);
}

// ==============================
// Core Functions
// ==============================
bool TDA7418Driver::setVolume(int volume) {
    if (volume < -80 || volume > 15) {
        AddLogError("TDA7418", "Invalid volume %d", volume);
        return false;
    }

    uint8_t val = (volume >= 0) ? volume : (0x10 + -volume);
    _registerData[REG_VOLUME] = val;
    return writeRegister(REG_VOLUME, val);
}

bool TDA7418Driver::setInput(uint8_t input) {
    if (input > 4) {
        AddLogError("TDA7418", "Invalid input %d", input);
        return false;
    }
    return updateRegister(REG_SOURCE_SEL, 0x07, input);
}

bool TDA7418Driver::setTone(int bass, int middle, int treble) {
    return setSpeakerLevels(bass, middle, treble, treble, bass);
}

bool TDA7418Driver::setLoudness(bool enable, uint8_t attenuation) {
    uint8_t val = (attenuation > 15) ? 0 : attenuation;
    _registerData[REG_LOUDNESS] = (enable ? 0x40 : 0x00) | (val & 0x0F);
    return writeRegister(REG_LOUDNESS, _registerData[REG_LOUDNESS]);
}

bool TDA7418Driver::setSpeakerLevels(int fl, int fr, int rl, int rr, int sub) {
    auto calc = [](int v) -> uint8_t {
        return (v >= 0) ? v : (0x10 + -v);
    };

    _registerData[REG_SPK_ATT_FL] = calc(fl);
    _registerData[REG_SPK_ATT_FR] = calc(fr);
    _registerData[REG_SPK_ATT_RL] = calc(rl);
    _registerData[REG_SPK_ATT_RR] = calc(rr);
    _registerData[REG_SPK_ATT_SUB] = calc(sub);

    return batchWrite(REG_SPK_ATT_FL, &_registerData[REG_SPK_ATT_FL], 5);
}

// ==============================
// Extra Features
// ==============================
bool TDA7418Driver::setMiddleQ(uint8_t q) {
    if (q > 3) return false;
    return updateRegister(REG_MIDDLE, 0x60, q << 5);
}

bool TDA7418Driver::setBassQ(uint8_t q) {
    if (q > 3) return false;
    return updateRegister(REG_BASS, 0x60, q << 5);
}

bool TDA7418Driver::setSoftMute(bool enable) {
    if (enable) {
        _registerData[REG_SOFTMUTE] &= ~(1 << 0);
    } else {
        _registerData[REG_SOFTMUTE] |= (1 << 0);
    }
    return writeRegister(REG_SOFTMUTE, _registerData[REG_SOFTMUTE]);
}

bool TDA7418Driver::setSmoothingFilter(bool enable) {
    if (enable) {
        _registerData[REG_MID_BAS_FC] |= (1 << 5);
    } else {
        _registerData[REG_MID_BAS_FC] &= ~(1 << 5);
    }
    return writeRegister(REG_MID_BAS_FC, _registerData[REG_MID_BAS_FC]);
}

// ==============================
// I2C Write Helpers
// ==============================
bool TDA7418Driver::writeRegister(uint8_t reg, uint8_t value) {
    for (uint8_t attempt = 0; attempt < MAX_I2C_RETRIES; attempt++) {
        _wire->beginTransmission(_i2cAddress);
        _wire->write(reg);
        _wire->write(value);
        if (_wire->endTransmission() == 0) {
            AddLogInfo("TDA7418", "Wrote reg 0x%02X = 0x%02X", reg, value);
            return true;
        }
        AddLogWarn("TDA7418", "Retry %d on reg 0x%02X", attempt + 1, reg);
    }
    AddLogError("TDA7418", "Failed reg 0x%02X", reg);
    StatusManager::SetError("TDA7418 I2C write failed");
    return false;
}

bool TDA7418Driver::batchWrite(uint8_t startReg, uint8_t* data, uint8_t length) {
    for (uint8_t attempt = 0; attempt < MAX_I2C_RETRIES; attempt++) {
        _wire->beginTransmission(_i2cAddress);
        _wire->write(startReg | AUTOINCREMENT);
        _wire->write(data, length);
        if (_wire->endTransmission() == 0) {
            AddLogInfo("TDA7418", "Batch write from 0x%02X (%d bytes)", startReg, length);
            return true;
        }
        AddLogWarn("TDA7418", "Batch retry %d from 0x%02X", attempt + 1, startReg);
    }
    AddLogError("TDA7418", "Batch write failed from 0x%02X", startReg);
    StatusManager::SetError("TDA7418 I2C batch write failed");
    return false;
}

bool TDA7418Driver::updateRegister(uint8_t reg, uint8_t mask, uint8_t value) {
    uint8_t current = _registerData[reg];
    current = (current & ~mask) | (value & mask);
    _registerData[reg] = current;
    return writeRegister(reg, current);
}
