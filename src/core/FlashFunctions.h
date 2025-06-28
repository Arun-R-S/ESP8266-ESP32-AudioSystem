#pragma once

#include <Arduino.h>

bool FlashRead(uint32_t address, void* data, size_t len);
bool FlashWrite(uint32_t address, const void* data, size_t len);
uint32_t CalculateCRC32(const uint8_t* data, size_t length);
