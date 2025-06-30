#include "Page_Home.h"
#include "../template/HtmlTemplate.h"
#include "../uiBlocks/HtmlLayout.h"
#include "../components/HtmlCard.h"

String HandleHomePage() {
    String pageBody = HtmlContainer(
        HtmlPageHeader("ESP Audio System", "Dashboard") +
        HtmlNavbar({{"/", "Home"}, {"/wifi", "WiFi"}, {"/audio", "Audio"}, {"/settings", "Settings"}}) +
        HtmlSection(
            HtmlCard("System Status", "Uptime: 5h<br>Version: 1.0.0") +
            HtmlCard("Quick Actions", "<a href='/wifi'>WiFi Setup</a><br><a href='/settings'>Settings</a>")
        ) +
        HtmlFooter("© 2025 ESP Audio System")
    );

    return HtmlPageTemplate("Home", pageBody);
}
