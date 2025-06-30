#include "WebServerManager.h"
#include "web/http/HttpRequest.h"
#include "web/http/HttpResponse.h"
#include "web/pages/Page_Home.h"

void WebServerManager::Begin(AsyncWebServer &server) {
    // ✅ Home page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *req) {
        HttpRequest request(req);
        HttpResponse response(req);
        response.SendHTML(HandleHomePage());
    });

    // // ✅ WiFi page
    // server.on("/wifi", HTTP_GET, [](AsyncWebServerRequest *req) {
    //     HttpRequest request(req);
    //     HttpResponse response(req);
    //     response.SendHTML(HandleWiFiPage());
    // });

    // // ✅ WiFi POST handler
    // server.on("/wifi_save", HTTP_POST, [](AsyncWebServerRequest *req) {
    //     HttpRequest request(req);
    //     HttpResponse response(req);
    //     String ssid = request.GetParam("ssid");
    //     String password = request.GetParam("password");
        
    //     // 🔸 Save WiFi credentials (call SettingsManager, etc.)
    //     // 🔸 Log and handle logic here

    //     response.Redirect("/wifi");
    // });

    // ✅ 404 handler
    server.onNotFound([](AsyncWebServerRequest *req) {
        HttpResponse res(req);
        res.SendError(404, "Not Found");
    });
}
