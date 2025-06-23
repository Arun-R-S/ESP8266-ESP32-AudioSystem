#include "AudioController.h"
#include <ArduinoLog.h>

bool AudioController::begin() {
  Log.info("AudioController begin() called\n");
  if (!audioIC.begin()) {
    Log.error("Audio IC initialization failed!\n");
    return false;
  }

  Log.info("AudioController initialized successfully.\n");
  return true;
}

void AudioController::setVolume(uint8_t vol) {
  audioIC.setVolume(vol);
}

uint8_t AudioController::getVolume() {
  return audioIC.getVolume();
}
