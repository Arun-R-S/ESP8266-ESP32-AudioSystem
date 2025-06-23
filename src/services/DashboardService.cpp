#include "DashboardService.h"

DashboardService::DashboardService(AsyncWebServer &server, AudioIC &audioIC)
  : _server(server), _audioIC(audioIC), _dash(&_server)
{
  // Initialize cards properly with CardType enum
  _volCard = new Card(&_dash, NUMBER_CARD, "Volume", "%");
  _bassCard = new Card(&_dash, NUMBER_CARD, "Bass", "dB");
  _trebleCard = new Card(&_dash, NUMBER_CARD, "Treble", "dB");
}

void DashboardService::begin() {
  // No setup needed for ESPDash itself
}

void DashboardService::update() {
  _volCard.update(String(_audioIC.getVolume()));
  _bassCard.update(String(_audioIC.getBass()));
  _trebleCard.update(String(_audioIC.getTreble()));
}