#pragma once

// =============================
// Select Board Type
// =============================
#if defined(ESP8266)
  #include "Board_ESP8266.h"
#elif defined(ESP32)
  #include "Board_ESP32.h"
#else
  #include "Board_Default.h"
#endif
