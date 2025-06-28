#include "HAL_EEPROM.h"
#include "core/Logger.h"
#include "boards/Board_Definitions.h"

#if defined(ESP8266)
  #include <EEPROM.h>
#elif defined(ESP32)
  #include <Preferences.h>
  Preferences preferences;
#endif

bool HAL_EEPROM::Begin(size_t size) {
#if defined(ESP8266)
    AddLogCore("HAL_EEPROM","Begin %s - size %d",BOARD_NAME,size);
    EEPROM.begin(size);
    return true;
#elif defined(ESP32)
    AddLogCore("HAL_EEPROM","Begin %s",BOARD_NAME)
    return preferences.begin("storage", false);
#else
    return false;
#endif
}

bool HAL_EEPROM::Read(size_t address, uint8_t* buffer, size_t length) {
#if defined(ESP8266)
    AddLogCore("HAL_EEPROM","Read %s",BOARD_NAME);
    for (size_t i = 0; i < length; i++) {
        buffer[i] = EEPROM.read(address + i);
    }
    return true;
#elif defined(ESP32)
    AddLogCore("HAL_EEPROM","Read %s",BOARD_NAME);
    for (size_t i = 0; i < length; i++) {
        buffer[i] = preferences.getUChar(String(address + i).c_str(), 0xFF);
    }
    return true;
#endif
}

bool HAL_EEPROM::Write(size_t address, const uint8_t* data, size_t length) {
#if defined(ESP8266)
    AddLogCore("HAL_EEPROM","Write %s",BOARD_NAME);
    for (size_t i = 0; i < length; i++) {
        EEPROM.write(address + i, data[i]);
    }
    return true;
#elif defined(ESP32)
    AddLogCore("HAL_EEPROM","Write %s",BOARD_NAME);
    for (size_t i = 0; i < length; i++) {
        preferences.putUChar(String(address + i).c_str(), data[i]);
    }
    return true;
#endif
}

bool HAL_EEPROM::Commit() {
#if defined(ESP8266)
    AddLogCore("HAL_EEPROM","Commit %s",BOARD_NAME);
    return EEPROM.commit();
#elif defined(ESP32)
    AddLogCore("HAL_EEPROM","Commit %s",BOARD_NAME);
    return true;
#endif
}

void HAL_EEPROM::End() {
#if defined(ESP8266)
    AddLogCore("HAL_EEPROM","END %s",BOARD_NAME);
    EEPROM.end();
#elif defined(ESP32)
    AddLogCore("HAL_EEPROM","END %s",BOARD_NAME);
    preferences.end();
#endif
}
