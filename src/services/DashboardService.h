#ifndef DASHBOARD_SERVICE_H
#define DASHBOARD_SERVICE_H

#include <ESPAsyncWebServer.h>
#include <ESPDash.h>
#include "AudioIC.h"

class DashboardService {
public:
    DashboardService(AsyncWebServer &server, AudioIC &audioIC);

    void begin();
    void updateVolume(int volume);
    void updateBass(int bass);
    void updateTreble(int treble);

private:
    AsyncWebServer &_server;
    ESPDash _dash;
    AudioIC &_audioIC;
    Card *_volCard;
    Card *_bassCard;
    Card *_trebleCard;

    void setupCards();
};

#endif // DASHBOARD_SERVICE_H
