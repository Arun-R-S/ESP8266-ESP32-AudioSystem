#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "../core/Logger.h"

class LCDDisplay {
public:
    LCDDisplay();

    bool begin();
    void clear();
    void printLine(uint8_t line, const String& message);
    void printLine(uint8_t row, const String& message);
    void showWelcomeMessage();
    void showError(const String& message);

private:
    LiquidCrystal_I2C lcd;
};

#endif // LCD_DISPLAY_H
