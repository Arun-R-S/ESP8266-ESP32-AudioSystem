#pragma once
#include <Wire.h>
#include "TDA7439.h"

class AudioController {
private:
  TDA7439 audioIC;
  int currentVolume = 30; // software-tracked volume

public:
  void begin() {
    Wire.begin();
    audioIC.setVolume(currentVolume); // no init() function
  }

  void increaseVolume() {
    if (currentVolume < 63) {
      currentVolume++;
      audioIC.setVolume(currentVolume);
    }
  }

  void decreaseVolume() {
    if (currentVolume > 0) {
      currentVolume--;
      audioIC.setVolume(currentVolume);
    }
  }

  int getVolume() const {
    return currentVolume;
  }

  void setVolume(int vol) {
    currentVolume = constrain(vol, 0, 63);
    audioIC.setVolume(currentVolume);
  }
};
