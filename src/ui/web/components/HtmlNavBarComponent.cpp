#include "HtmlNavBarComponent.h"

String HtmlNavBarComponent() {
                    
    return 
    HtmlDiv(
        HtmlDiv(
            //HtmlLink(GlobalConstants::appName, "#", "navbar-brand") +
                HtmlButton(
                    "<span class='navbar-toggler-icon'></span>", // You can wrap this using HtmlSpan if needed
                    HtmlAttrs({{"class", "navbar-toggler"},
                               {"type", "button"},
                               {"data-bs-toggle", "collapse"},
                               {"data-bs-target", "#navbarNavAltMarkup"},
                               {"aria-controls", "navbarNavAltMarkup"},
                               {"aria-expanded", "false"},
                               {"aria-label", "Toggle navigation"}})) +
                HtmlDiv(
                    HtmlDiv(
                        HtmlLink("/", "Home", HtmlAttrs({{"class", "nav-link"}, {"aria-current", "page"}})) +
                            HtmlLink("/wifi", "WiFi", HtmlAttrs({{"class", "nav-link"}, {"aria-current", "page"}})) +
                            HtmlLink("/audio", "Audio", HtmlAttrs({{"class", "nav-link"}, {"aria-current", "page"}})) +
                            HtmlLink("/settings", "Settings", HtmlAttrs({{"class", "nav-link"}, {"aria-current", "page"}, {"tabindex", "-1"}, {"aria-disabled", "true"}})),
                        HtmlAttr("class", "navbar-nav")),
                    HtmlAttrs({{"class", "collapse navbar-collapse"},
                               {"id", "navbarNavAltMarkup"}})),
            HtmlAttr("class", "container-fluid")),
        HtmlAttr("class", "navbar navbar-expand-lg bg-body-tertiary"));
}
