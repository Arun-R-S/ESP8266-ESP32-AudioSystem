#include <Arduino.h>
#include "Logger.h"
#include "ButtonHandler.h"
#include "AudioController.h"
AudioController audio;


ButtonHandler buttonHandler;

void handleButtonEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.print(F("Button Event: "));
  Serial.println(eventType);
}

void setup() {
  Serial.begin(115200);
  Logger::setLogLevel(LOG_INFO); // or LOG_ERROR, LOG_WARNING

  Logger::info("Setup started");

  if (audio.begin()) {
  Logger::info("TDA7439 initialized successfully via AudioController.\n");
} else {
  Logger::error("TDA7439 init failed via AudioController!\n");
}

  Logger::info("Setup completed");
  buttonHandler.begin(handleButtonEvent);
}


void loop() {
  buttonHandler.checkButtons();
}
