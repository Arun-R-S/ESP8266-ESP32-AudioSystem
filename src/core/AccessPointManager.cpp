#include "AccessPointManager.h"
#include "config/SettingsManager.h"
#include "Logger.h"

#if defined(ESP8266)
ESP8266WebServer server(80);
#else
WebServer server(80);
#endif

// ✅ Implement Singleton Instance
AccessPointManager& AccessPointManager::Instance() {
    static AccessPointManager instance;
    return instance;
}

void HandleRoot() {
    String html = "<html><body><h2>WiFi Configuration</h2><form method='POST' action='/save'>";
    html += "SSID: <input name='ssid'><br>";
    html += "Password: <input name='password' type='password'><br>";
    html += "<input type='submit' value='Save'></form></body></html>";
    server.send(200, "text/html", html);
}

void HandleSave() {
    String ssid = server.arg("ssid");
    String pass = server.arg("password");

    Settings.wifiSettings.ssid = ssid;
    Settings.wifiSettings.password = pass;
    if(SettingsManager::Instance().SaveSettings())
    {
        server.send(200, "text/html", "<h3>Settings saved. Restart device.</h3>");
        AddLogInfo("WiFi", "WiFi credentials saved via AP");

        delay(2000);
        ESP.restart();
    }
    else{
        server.send(200, "text/html", "<h3>Error Saving Settings</h3>");
        AddLogInfo("WiFi", "WiFi credentials saved via AP");
    }
}

void AccessPointManager::Start(const char* ssid, const char* password) {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    AddLogInfo("WiFi", "AP IP address: %s", IP.toString().c_str());

    server.on("/", HandleRoot);
    server.on("/save", HandleSave);
    server.begin();
}

void AccessPointManager::HandleClient() {
    server.handleClient();
}