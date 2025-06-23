// DashboardService.cpp
#include "DashboardService.h"

DashboardService::DashboardService(AsyncWebServer &server, AudioIC &audioIC)
    : _server(server), _audioIC(audioIC), _dash(&_server)
{
    // Initialize ESPDash with the server reference
}

void DashboardService::setup() {
    _volCard = new Card(&_dash, NUMBER_CARD, "Volume", "%");
    _bassCard = new Card(&_dash, NUMBER_CARD, "Bass", "dB");
    _trebleCard = new Card(&_dash, NUMBER_CARD, "Treble", "dB");
}

void DashboardService::update() {
    _volCard->update(_audioIC.getVolume());
    _bassCard->update(_audioIC.getBass());
    _trebleCard->update(_audioIC.getTreble());
}
