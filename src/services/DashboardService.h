// DashboardService.h
#ifndef DASHBOARD_SERVICE_H
#define DASHBOARD_SERVICE_H

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>
#include "../audio/AudioIC.h"

class DashboardService {
public:
    DashboardService(AsyncWebServer &server, AudioIC &audioIC);

    void setup();
    void update();

private:
    AsyncWebServer &_server;
    AudioIC &_audioIC;
    ESPDash _dash;

    // Cards
    Card *_volCard;
    Card *_bassCard;
    Card *_trebleCard;
};

#endif
