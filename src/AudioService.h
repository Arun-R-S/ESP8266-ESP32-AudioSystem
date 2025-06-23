#pragma once
#include <TDA7439.h>

class AudioService {
private:
  TDA7439 audioIC;

public:
  void begin() {
    audioIC.init();
    Log.notice(F("Audio IC initialized.\n"));
  }

  void setVolume(uint8_t vol) {
    audioIC.setVolume(vol);
    Log.notice(F("Volume set to %d\n"), vol);
  }

  void volumeUp() {
    audioIC.setVolume(audioIC.getCurrentVolume() + 1);
  }

  void volumeDown() {
    audioIC.setVolume(audioIC.getCurrentVolume() - 1);
  }

  uint8_t getVolume() {
    return audioIC.getCurrentVolume();
  }
};
