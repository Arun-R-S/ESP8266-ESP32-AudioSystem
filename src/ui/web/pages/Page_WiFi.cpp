#include "Page_WiFi.h"
#include "config/SettingsStruct.h"
#include "../template/HtmlTemplate.h"
#include "../uiBlocks/HtmlLayout.h"
#include "../components/HtmlCard.h"
#include "core/SystemManager.h"
#include "global/GlobalConstants.h"
#include "ui/web/elements/SystemElements.h"
#include "ui/web/fields/HtmlTags.h"
#include "ui/web/components/HtmlNavBarComponent.h"
#include <ESP8266WiFi.h>

String HandleWiFiPage()
{
    String pageBody = HtmlContainer(
        HtmlPageHeader("ESP Audio System", "Wifi") +
        // HtmlNavbar({{"/", "Home"}, {"/wifi", "WiFi"}, {"/audio", "Audio"}, {"/settings", "Settings"}}) +
        HtmlNavBarComponent() +
        HtmlSection(
            HtmlCard("Wifi Status", "SSID: " +String(Settings.wifiSettings.ssid) + "<br>Static IP: " + WiFi.localIP().toString()
              + "<br> Gateway: "+ WiFi.gatewayIP().toString()
              + "<br> Subnet: "+ WiFi.subnetMask().toString()  )
            // + HtmlCard("Quick Actions", "<a href='/wifi'>WiFi Setup</a><br><a href='/settings'>Settings</a>")
            ) +
        HtmlFooter("© <script>document.write(new Date().getFullYear());</script> " + GlobalConstants::appName));

    return HtmlPageTemplate(GlobalConstants::webAppName, pageBody);
}
