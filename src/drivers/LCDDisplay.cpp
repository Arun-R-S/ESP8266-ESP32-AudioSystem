#include "LCDDisplay.h"

LCDDisplay::LCDDisplay() : lcd(0x27, 16, 2) {
    // I2C address 0x27 is default for most 16x2 modules
}

bool LCDDisplay::begin() {
    try {
        lcd.init();
        lcd.backlight();
        lcd.clear();
        Logger::info("LCD initialized");
        return true;
    } catch (...) {
        Logger::error("LCD init failed");
        return false;
    }
}

void LCDDisplay::clear() {
    try {
        lcd.clear();
    } catch (...) {
        Logger::error("LCD clear failed");
    }
}

void LCDDisplay::printLine(uint8_t line, const String& message) {
    try {
        lcd.setCursor(0, line);
        lcd.print("                ");  // clear previous content
        lcd.setCursor(0, line);
        lcd.print(message);
        Logger::debug("LCD line %d: %s", line, message.c_str());
    } catch (...) {
        Logger::error("LCD print failed on line %d", line);
    }
}

void LCDDisplay::showWelcomeMessage() {
    printLine(0, "ESP Audio Ctrl");
    printLine(1, "Booting...");
}

void LCDDisplay::showError(const String& message) {
    clear();
    printLine(0, "ERROR:");
    printLine(1, message.substring(0, 16)); // Limit to display size
}
