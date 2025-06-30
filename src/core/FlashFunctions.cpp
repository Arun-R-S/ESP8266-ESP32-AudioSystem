#include "FlashFunctions.h"
#include "Logger.h"

#if defined(ESP8266)
#include <ESP.h>

#elif defined(ESP32)
#include <esp_spi_flash.h>

#else
#error "Unsupported platform"
#endif

bool FlashRead(uint32_t address, void *data, size_t len)
{
#if defined(ESP8266)
    AddLogCore("Flash ESP8266", "Read");
    return ESP.flashRead(address, (uint32_t *)data, len) == true;
#elif defined(ESP32)
    AddLogCore("Flash ESP32", "Read");
    return spi_flash_read(address, data, len) == ESP_OK;
#endif
}

bool FlashWrite(uint32_t address, const void *data, size_t len)
{
#if defined(ESP8266)
    AddLogCore("Flash ESP8266", "Write");
    return ESP.flashEraseSector(address / 4096) &&
           ESP.flashWrite(address, (uint32_t *)data, len);
#elif defined(ESP32)
    AddLogCore("Flash ESP32", "Write");
    spi_flash_erase_range(address, 4096); // Always erase before write
    return spi_flash_write(address, data, len) == ESP_OK;
#endif
}

bool FlashWriteWithWearReduction(uint32_t address, const void *data, size_t len) {
    const uint32_t sectorSize = 4096;
    uint32_t sectorStart = address & ~(sectorSize - 1);
    uint32_t offset = address - sectorStart;

    uint8_t buffer[sectorSize]; // RAM buffer of the full sector

    const uint8_t* src = (const uint8_t*)data; // Cast for pointer arithmetic

    // Read existing sector into buffer
    #if defined(ESP8266)
    if (!ESP.flashRead(sectorStart, (uint32_t *)buffer, sectorSize)) {
        AddLogCore("Flash", "Read failed");
        return false;
    }
    #elif defined(ESP32)
    if (spi_flash_read(sectorStart, (uint32_t *)buffer, sectorSize) != ESP_OK) {
        AddLogCore("Flash", "Read failed");
        return false;
    }
    #endif

    // Check if write is necessary
    bool needsWrite = false;
    for (uint32_t i = 0; i < len; i++) {
        if (buffer[offset + i] != src[i]) {
            needsWrite = true;
            buffer[offset + i] = src[i];  // Update buffer for write
        }
    }

    if (!needsWrite) {
        AddLogCore("Flash", "Skip write, data identical");
        return true;
    }

    // Erase sector
    #if defined(ESP8266)
    if (!ESP.flashEraseSector(sectorStart / sectorSize)) {
        AddLogCore("Flash", "Erase failed");
        return false;
    }

    if (!ESP.flashWrite(sectorStart, (uint32_t*)buffer, sectorSize)) {
        AddLogError("Flash", "Write failed");
        return false;
    }

    #elif defined(ESP32)
    if (spi_flash_erase_range(sectorStart, sectorSize) != ESP_OK) {
        AddLogCore("Flash", "Erase failed");
        return false;
    }

    if (spi_flash_write(sectorStart, (uint32_t*)buffer, sectorSize) != ESP_OK) {
        AddLogError("Flash", "Write failed");
        return false;
    }
    #endif

    AddLogInfo("Flash", "Write completed at 0x%08X", address);
    return true;
}



uint32_t CalculateCRC32(const uint8_t *data, size_t length)
{
    AddLogCore("FlashFunctions", "CalculateCRC32 Enter");
    uint32_t crc = 0xFFFFFFFF;
    while (length--)
    {
        crc ^= *data++;
        for (uint8_t i = 0; i < 8; i++)
            crc = (crc >> 1) ^ (0xEDB88320UL & -(crc & 1));
    }
    AddLogCore("FlashFunctions", "CalculateCRC32 Exit");
    AddLogCore("FlashFunctions", "return value %d", crc);
    return ~crc;
}
