#pragma once

#include "BoardInterface.h"

#if defined(ESP8266)
#include "ESP8266Board.cpp"
inline BoardInterface* createBoard() { return new ESP8266Board(); }

#elif defined(ESP32)
#include "ESP32Board.cpp"
inline BoardInterface* createBoard() { return new ESP32Board(); }

#else
#error "Unsupported board"
#endif
