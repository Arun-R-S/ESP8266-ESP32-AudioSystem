#pragma once
#include <cstdint>

#if defined(ESP8266)
// Example for NodeMCU
constexpr uint8_t DEFAULT_SDA = 4;  // D2
constexpr uint8_t DEFAULT_SCL = 5;  // D1
#elif defined(ESP32)
// Example for ESP32 DevKit
constexpr uint8_t DEFAULT_SDA = 21;
constexpr uint8_t DEFAULT_SCL = 22;
#endif
