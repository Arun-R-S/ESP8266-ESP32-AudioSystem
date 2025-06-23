#pragma once
#include <LiquidCrystal_I2C.h>

class LCDService {
private:
  LiquidCrystal_I2C lcd;

public:
  LCDService(uint8_t addr = 0x27, uint8_t cols = 16, uint8_t rows = 2)
    : lcd(addr, cols, rows) {}

  void begin() {
    lcd.begin(16, 2);
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("LCD Ready");
  }

  void printLine(uint8_t line, const String& text) {
    lcd.setCursor(0, line);
    lcd.print("                "); // clear line
    lcd.setCursor(0, line);
    lcd.print(text);
  }
};
