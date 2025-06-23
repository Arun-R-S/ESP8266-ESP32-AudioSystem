#include "DashboardService.h"
#include "../core/Logger.h"

DashboardService::DashboardService(AsyncWebServer &server, AudioIC &audioIC)
    : _server(server), _dash(&_server), _audioIC(audioIC),
      _volCard(nullptr), _bassCard(nullptr), _trebleCard(nullptr) {}

void DashboardService::begin() {
    Logger::info("DashboardService: Initializing dashboard");
    _dash.begin();

    setupCards();
    _dash.start();

    Logger::info("DashboardService: Dashboard running at http://%s/", WiFi.localIP().toString().c_str());
}

void DashboardService::setupCards() {
    _volCard = _dash.createCard(Stat, "Volume", "#");
    _bassCard = _dash.createCard(Stat, "Bass", "#");
    _trebleCard = _dash.createCard(Stat, "Treble", "#");
}

void DashboardService::updateVolume(int volume) {
    if (_volCard) {
        _volCard->setValue(volume);
        _dash.updateCard(_volCard);
    }
}

void DashboardService::updateBass(int bass) {
    if (_bassCard) {
        _bassCard->setValue(bass);
        _dash.updateCard(_bassCard);
    }
}

void DashboardService::updateTreble(int treble) {
    if (_trebleCard) {
        _trebleCard->setValue(treble);
        _dash.updateCard(_trebleCard);
    }
}
