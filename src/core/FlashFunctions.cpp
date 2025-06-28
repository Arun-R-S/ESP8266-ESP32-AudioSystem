#include "FlashFunctions.h"

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
    return ESP.flashRead(address, (uint32_t *)data, len) == true;
#elif defined(ESP32)
    return spi_flash_read(address, data, len) == ESP_OK;
#endif
}

bool FlashWrite(uint32_t address, const void *data, size_t len)
{
#if defined(ESP8266)
    return ESP.flashEraseSector(address / 4096) &&
           ESP.flashWrite(address, (uint32_t *)data, len);
#elif defined(ESP32)
    spi_flash_erase_range(address, 4096); // Always erase before write
    return spi_flash_write(address, data, len) == ESP_OK;
#endif
}

uint32_t CalculateCRC32(const uint8_t *data, size_t length)
{
    uint32_t crc = 0xFFFFFFFF;
    while (length--)
    {
        crc ^= *data++;
        for (uint8_t i = 0; i < 8; i++)
            crc = (crc >> 1) ^ (0xEDB88320UL & -(crc & 1));
    }
    return ~crc;
}
