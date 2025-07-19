#include "WebRouter_Wifi.h"
#include "../Http/HttpRequest.h"
#include "../Http/HttpResponse.h"
#include "ui/web/elements/SystemElements.h"

void RegisterSysRoutes(AsyncWebServer &server)
{
    server.on("/stat", HTTP_GET, [](AsyncWebServerRequest *req)
    {
        HttpRequest request(req);
        HttpResponse response(req);

        String html = "";

        int paramCount = req->params();
        for (int i = 0; i < paramCount; ++i) {
            const AsyncWebParameter* p = req->getParam(i);
            if (p->name() == F("sys")) {
                String value = p->value();
                if (value == F("upt")) {
                    html += SystemElements::UpTime(true);
                } else if (value == F("uram")) {
                    html += SystemElements::RamUsage(true);
                }
                // You can extend this to support more values:
                // else if (value == "cpu") { html += SystemElements::CpuUsage(true); }
            }
        }

        if (html.isEmpty()) {
            html = "<h2>No valid system parameters provided.</h2>";
        }

        response.SendHTML(html); 
    });
}
