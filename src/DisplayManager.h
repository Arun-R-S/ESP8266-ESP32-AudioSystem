#pragma once
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class DisplayManager {
private:
  LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Default address

public:
  void begin() {
    lcd.begin(16, 2);
    lcd.backlight();
    lcd.clear();
  }

  void print(const String& text, int col = 0, int row = 0) {
    lcd.setCursor(col, row);
    lcd.print(text);
  }

  void clear() {
    lcd.clear();
  }
};
