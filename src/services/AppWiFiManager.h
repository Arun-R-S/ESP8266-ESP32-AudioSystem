#pragma once
#include <ESPAsyncWebServer.h>

class AppWiFiManager {
  public:
    AppWiFiManager(AsyncWebServer &server);
    void begin();
    void handle();

  private:
    AsyncWebServer &_server;
};