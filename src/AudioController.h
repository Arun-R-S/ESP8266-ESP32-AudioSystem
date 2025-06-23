#pragma once
#include <TDA7439.h>

class AudioController {
  public:
    bool begin();
    void setVolume(uint8_t vol);
    uint8_t getVolume();

  private:
    TDA7439 audioIC;
};
