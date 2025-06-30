#include "HtmlCard.h"

String HtmlCard(const String& title,
                const String& content,
                const String& footer,
                const String& cardAttributes) {
                    
    String card = "";

    // 🔹 Title/Header Section
    if (title.length()) {
        card += HtmlDiv(title, HtmlAttrs({{"class", "card-header"}}));
    }

    // 🔸 Content/Body Section
    card += HtmlDiv(content, HtmlAttrs({{"class", "card-body"}}));

    // 🔹 Footer Section (optional)
    if (footer.length()) {
        card += HtmlDiv(footer, HtmlAttrs({{"class", "card-footer"}}));
    }

    return HtmlDiv(card, 
                   HtmlAttrs({{"class", "card"}}) + 
                   (cardAttributes.length() ? " " + cardAttributes : ""));
}
