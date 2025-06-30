#include "I2CBus.h"
#include <Wire.h>
#include "core/Logger.h"
#include "core/StatusManager.h"
#include "config/SettingsStruct.h"

I2CBus::I2CBus(uint8_t sda, uint8_t scl) : _sda(sda), _scl(scl) {}

bool I2CBus::Init() {
    Wire.begin(_sda, _scl);
    AddLogInfo("I2CBus", "Wire initialized on SDA:%d, SCL:%d", _sda, _scl);
    StatusManager::ClearError("I2C");
    return true;
}

// ========= WRITE with Register =========
bool I2CBus::Write(uint8_t address, uint8_t reg, uint8_t data, uint8_t retries) {
    for (uint8_t i = 0; i <= retries; i++) {
        if (PerformWrite(address, reg, data)) {
            StatusManager::ClearError("I2C");
            return true;
        }
        AddLogWarn("I2CBus", "Write retry %d to 0x%02X failed", i + 1, address);
        delay(50);
    }
    StatusManager::SetError("I2C", ERROR_I2C_COMMUNICATION);
    return false;
}

// ========= WRITE Buffer =========
bool I2CBus::Write(uint8_t address, const uint8_t* data, uint8_t length, uint8_t retries) {
    for (uint8_t i = 0; i <= retries; i++) {
        if (PerformWrite(address, data, length)) {
            StatusManager::ClearError("I2C");
            return true;
        }
        AddLogWarn("I2CBus", "Write buffer retry %d to 0x%02X failed", i + 1, address);
        delay(50);
    }
    StatusManager::SetError("I2C", ERROR_I2C_COMMUNICATION);
    return false;
}

// ========= READ =========
bool I2CBus::Read(uint8_t address, uint8_t reg, uint8_t& data, uint8_t retries) {
    for (uint8_t i = 0; i <= retries; i++) {
        if (PerformRead(address, reg, data)) {
            StatusManager::ClearError("I2C");
            return true;
        }
        AddLogWarn("I2CBus", "Read retry %d from 0x%02X failed", i + 1, address);
        delay(50);
    }
    StatusManager::SetError("I2C", ERROR_I2C_COMMUNICATION);
    return false;
}

// ========= DETECT =========
bool I2CBus::Detect(uint8_t address) {
    Wire.beginTransmission(address);
    return Wire.endTransmission() == 0;
}

// ========= PRIVATE Low-Level WRITE =========
bool I2CBus::PerformWrite(uint8_t address, uint8_t reg, uint8_t data) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(data);
    return Wire.endTransmission() == 0;
}

bool I2CBus::PerformWrite(uint8_t address, const uint8_t* data, uint8_t length) {
    Wire.beginTransmission(address);
    Wire.write(data, length);
    return Wire.endTransmission() == 0;
}

// ========= PRIVATE Low-Level READ =========
bool I2CBus::PerformRead(uint8_t address, uint8_t reg, uint8_t& data) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0) {
        return false;
    }

    if (Wire.requestFrom(address, (uint8_t)1) != 1) {
        return false;
    }

    data = Wire.read();
    return true;
}

// ========= SCAN =========
void I2CBus::Scan() {
    AddLogInfo("I2CBus", "Scanning for I2C devices...");

    uint8_t count = 0;
    for (uint8_t address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        uint8_t error = Wire.endTransmission();

        if (error == 0) {
            AddLogInfo("I2CBus", "Found device at 0x%02X", address);
            count++;
        }
    }
    if (count == 0) {
        AddLogWarn("I2CBus", "No I2C devices found.");
    } else {
        AddLogInfo("I2CBus", "Scan complete. %d device(s) found.", count);
    }
}
