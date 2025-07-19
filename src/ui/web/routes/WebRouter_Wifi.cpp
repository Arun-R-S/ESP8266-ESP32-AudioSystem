#include "WebRouter_Wifi.h"
#include "../Http/HttpRequest.h"
#include "../Http/HttpResponse.h"
#include "../pages/Page_WiFi.h"

void RegisterWifiRoutes(AsyncWebServer& server) {
    server.on("/wifi", HTTP_GET, [](AsyncWebServerRequest *req) {
        HttpRequest request(req);
        HttpResponse response(req);
        response.SendHTML(HandleWiFiPage());
    });
}
