#include "Page_Home.h"
#include "../template/HtmlTemplate.h"
#include "../uiBlocks/HtmlLayout.h"
#include "../components/HtmlCard.h"
#include "core/SystemManager.h"
#include "global/GlobalConstants.h"
#include "ui/web/elements/SystemElements.h"
#include "ui/web/fields/HtmlTags.h"
#include "ui/web/components/HtmlNavBarComponent.h"

String HandleHomePage()
{
    String pageBody = HtmlContainer(
        HtmlPageHeader("ESP Audio System", "Home") +
        // HtmlNavbar({{"/", "Home"}, {"/wifi", "WiFi"}, {"/audio", "Audio"}, {"/settings", "Settings"}}) +
        HtmlNavBarComponent() +
        HtmlSection(
            HtmlCard("System Status", "Uptime: " + SystemElements::UpTime(true) + "<br>Version: " + GlobalConstants::softwareVersion
              + "<br> Ram Usage: "+ SystemElements::RamUsage(true)  )
            // + HtmlCard("Quick Actions", "<a href='/wifi'>WiFi Setup</a><br><a href='/settings'>Settings</a>")
            ) +
        HtmlFooter("© <script>document.write(new Date().getFullYear());</script> " + GlobalConstants::appName));

    return HtmlPageTemplate(GlobalConstants::webAppName, pageBody);
}
