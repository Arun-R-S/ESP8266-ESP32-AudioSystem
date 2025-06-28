#include "DisplayUI.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void DisplayUI::Begin() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ESP Audio");
    lcd.setCursor(0, 1);
    lcd.print("Starting...");
}

void DisplayUI::ShowStatus() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("IP:");
    lcd.setCursor(3, 0);
    //lcd.print(WiFi.localIP());

    lcd.setCursor(0, 1);
    lcd.print("Vol:");
    lcd.print("10"); // replace with actual
}

void DisplayUI::ShowVolume(int volume) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Volume:");
    lcd.setCursor(0, 1);
    lcd.print(volume);
}

void DisplayUI::ShowMenu(const char* menu) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Menu:");
    lcd.setCursor(0, 1);
    lcd.print(menu);
}
