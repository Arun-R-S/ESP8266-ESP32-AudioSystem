#include "I2CBus.h"
#include <Wire.h>
#include "core/Logger.h"

I2CBus::I2CBus(uint8_t sda, uint8_t scl) : _sda(sda), _scl(scl) {}

bool I2CBus::Init() {
#ifdef ESP8266
    Wire.begin(_sda, _scl);
    AddLogInfo("I2CBus","Wire Init");
#elif defined(ESP32)
    Wire.begin(_sda, _scl);
    AddLogInfo("I2CBus","Wire Init");
#endif
    return true;
}

bool I2CBus::Write(uint8_t address, uint8_t reg, uint8_t data) {
    AddLogCore("I2CBus","Write at address 0x%02X and reg 0x%02X = 0x%02X",address, reg, data);
    AddLogCore("I2CBus","Begin Tansmission");
    Wire.beginTransmission(address);
    AddLogCore("I2CBus","Write");
    Wire.write(reg);
    Wire.write(data);
    AddLogCore("I2CBus","Will end Transmission");
    return Wire.endTransmission() == 0;
}

bool I2CBus::Write(uint8_t address, const uint8_t* data, uint8_t length) {
    Wire.beginTransmission(address);
    Wire.write(data, length);
    return Wire.endTransmission() == 0;
}

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
    AddLogDebugMore("I2CBus Scan","Count -> %d",count);
    if (count == 0) {
        AddLogWarn("I2CBus", "No I2C devices found.");
    } else {
        AddLogInfo("I2CBus", "Scan complete. %d device(s) found.", count);
    }
    AddLogDebug("I2CBus", "I2C Scan function completed.");
}
