#include <Arduino.h>
#include "ButtonHandler.h"

ButtonHandler buttonHandler;

void handleButtonEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.print(F("Button Event: "));
  Serial.println(eventType);
}

void setup() {
  Serial.begin(115200);
  buttonHandler.begin(handleButtonEvent);
}

void loop() {
  buttonHandler.checkButtons();
}
