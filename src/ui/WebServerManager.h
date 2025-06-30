#pragma once
#include <ESPAsyncWebServer.h>

class WebServerManager {
public:
    static void Begin(AsyncWebServer &server);
};
