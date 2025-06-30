#include "AccessPointManager.h"
#include "config/SettingsManager.h"
#include "Logger.h"

#if defined(ESP8266)
AsyncWebServer server(80);
#else
WebServer server(80);
#endif


// ✅ Singleton Instance
AccessPointManager& AccessPointManager::Instance() {
    static AccessPointManager instance;
    return instance;
}

void AccessPointManager::Start(const char* ssid, const char* password) {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    AddLogInfo("WiFi", "AP IP address: %s", IP.toString().c_str());

    // 🔥 Route: Root Form
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html;
        html += "<html><body><h2>WiFi Configuration</h2><form method='POST' action='/save'>";
        html += "SSID: <input name='ssid'><br>";
        html += "Password: <input name='password' type='password'><br>";
        html += "<input type='submit' value='Save'></form></body></html>";
        request->send(200, "text/html", html);
    });

    // 🔥 Route: Save WiFi credentials
    server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request) {
        String ssid, pass;

        if (request->hasParam("ssid", true)) {
            ssid = request->getParam("ssid", true)->value();
        }
        if (request->hasParam("password", true)) {
            pass = request->getParam("password", true)->value();
        }

        strncpy(Settings.wifiSettings.ssid, ssid.c_str(), sizeof(Settings.wifiSettings.ssid) - 1);
        Settings.wifiSettings.ssid[sizeof(Settings.wifiSettings.ssid) - 1] = '\0';

        strncpy(Settings.wifiSettings.password, pass.c_str(), sizeof(Settings.wifiSettings.password) - 1);
        Settings.wifiSettings.password[sizeof(Settings.wifiSettings.password) - 1] = '\0';

        if (SettingsManager::Instance().SaveSettings()) {
            request->send(200, "text/html", "<h3>Settings saved. Restarting...</h3>");
            AddLogInfo("WiFi", "WiFi credentials saved via AP");
            delay(2000);
            ESP.restart();
        } else {
            request->send(200, "text/html", "<h3>Error saving settings</h3>");
            AddLogError("WiFi", "Error saving WiFi settings via AP");
        }
    });

    // ✅ Start Server
    server.begin();
}

// ✅ No handleClient required for Async
void AccessPointManager::HandleClient() {
    // No-op for Async
}