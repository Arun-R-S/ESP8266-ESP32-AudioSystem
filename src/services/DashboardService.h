#pragma once
#include <ESPDash.h>
#include "drivers/AudioIC.h"

class DashboardService {
  public:
    DashboardService(AsyncWebServer &server, AudioIC &audioIC);
    void begin();
    void update();

  private:
    ESPDash _dashboard;
    Card _volCard;
    Card _bassCard;
    Card _trebleCard;
    AudioIC &_audioIC;
};