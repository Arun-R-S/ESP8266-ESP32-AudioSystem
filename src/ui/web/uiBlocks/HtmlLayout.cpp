#include "HtmlLayout.h"

// ✅ Page Header Block
String HtmlPageHeader(const String& title, const String& subtitle) {
    String html = HtmlHeader(1, title);
    if (subtitle.length()) {
        html += HtmlParagraph(subtitle, HtmlAttrs({{"class", "subtitle"}}));
    }
    return HtmlDiv(html, HtmlAttrs({{"class", "page-header"}}));
}

// ✅ Navbar Block
String HtmlNavbar(const std::vector<std::pair<String, String>>& links) {
    String navContent;
    for (const auto& link : links) {
        navContent += HtmlLink(link.first, link.second, HtmlAttrs({{"class", "nav-link"}}));
    }
    return HtmlDiv(navContent, HtmlAttrs({{"class", "navbar"}}));
}

// ✅ Footer Block
String HtmlFooter(const String& content) {
    return HtmlDiv(content, HtmlAttrs({{"class", "footer"}}));
}

// ✅ Generic Container Block
String HtmlContainer(const String& content, const String& attributes) {
    return HtmlDiv(content, HtmlAttrs({{"class", "container"}}) + 
                   (attributes.length() ? " " + attributes : ""));
}

// ✅ Section Block
String HtmlSectionBlock(const String& content, const String& attributes) {
    return HtmlDiv(content, HtmlAttrs({{"class", "section"}}) + 
                   (attributes.length() ? " " + attributes : ""));
}
