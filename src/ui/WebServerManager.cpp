#include "WebServerManager.h"
#include "web/http/HttpRequest.h"
#include "web/http/HttpResponse.h"
#include "web/pages/Page_Home.h"
#include "core/Logger.h"
#include "config/SettingsManager.h"
#include "web/routes/WebRouter_Wifi.h"
#include "web/routes/WebRouter_Sys.h"

void WebServerManager::Begin(AsyncWebServer &server) {
    // ✅ Home page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *req) {
        HttpRequest request(req);
        HttpResponse response(req);
        if (WiFi.getMode() == WIFI_AP) {
            response.SendHTML(R"rawliteral(<script src="https://cdn.jsdelivr.net/npm/@tailwindcss/browser@4"></script>
                <h2>WiFi Configuration</h2>
                <form action="/savewifi" method="POST">
                  SSID: <input type="text" name="ssid"><br><br>
                  Password: <input type="password" name="password"><br><br>
                  <input type="submit" value="Save">
                </form>
            )rawliteral",200);
        } else {
        response.SendHTML(HandleHomePage());
        }
    });

    // Save WiFi credentials
    server.on("/savewifi", HTTP_POST, [](AsyncWebServerRequest *request) {
        String ssid = request->arg("ssid");
        String password = request->arg("password");

        ssid.trim();
        password.trim();

        if (ssid.length() > 0) {
            strncpy(Settings.wifiSettings.ssid, ssid.c_str(), sizeof(Settings.wifiSettings.ssid) - 1);
            strncpy(Settings.wifiSettings.password, password.c_str(), sizeof(Settings.wifiSettings.password) - 1);

            if(SettingsManager::Instance().SaveSettings())
            {
                AddLogInfo("WebServerManager", "WiFi credentials saved. SSID: %s", ssid.c_str());

                request->send(200, "text/html", "<h2>Saved. Rebooting...</h2>");
                delay(1000);
                ESP.restart();
            }
            else{
                request->send(404, "text/html", "<h1>Failed to save</h1><br>Go to <a href=''>Home</a>");
            }
            
        } else {
            request->send(200, "text/html", "<h2>SSID cannot be empty</h2>");
        }
    });
    RegisterWifiRoutes(server);
    RegisterSysRoutes(server);
    server.begin();
    AddLogInfo("WebServerManager", "Web UI Started.");

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
