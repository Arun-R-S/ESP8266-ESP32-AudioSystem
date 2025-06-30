#include "HtmlTags.h"



// ✅ Common Tag Shortcuts
String HtmlDiv(const String& content, const String& attributes) {
    return HtmlTag("div", content, attributes);
}

String HtmlSpan(const String& content, const String& attributes) {
    return HtmlTag("span", content, attributes);
}

String HtmlParagraph(const String& content, const String& attributes) {
    return HtmlTag("p", content, attributes);
}

String HtmlHeader(int level, const String& content, const String& attributes) {
    level = constrain(level, 1, 6);
    return HtmlTag("h" + String(level), content, attributes);
}

String HtmlSection(const String& content, const String& attributes) {
    return HtmlTag("section", content, attributes);
}

String HtmlArticle(const String& content, const String& attributes) {
    return HtmlTag("article", content, attributes);
}

String HtmlLabel(const String& content, const String& attributes) {
    return HtmlTag("label", content, attributes);
}

String HtmlForm(const String& content, const String& attributes) {
    return HtmlTag("form", content, attributes);
}

String HtmlButton(const String& content, const String& attributes) {
    return HtmlTag("button", content, attributes);
}

String HtmlLink(const String& href, const String& text, const String& attributes) {
    String attrs = HtmlAttr("href", href);
    if (attributes.length()) attrs += " " + attributes;
    return HtmlTag("a", text, attrs);
}

String HtmlImage(const String& src, const String& attributes) {
    String attrs = HtmlAttr("src", src);
    if (attributes.length()) attrs += " " + attributes;
    return HtmlSelfClosingTag("img", attrs);
}

String HtmlInput(const String& attributes) {
    return HtmlSelfClosingTag("input", attributes);
}

String HtmlTextarea(const String& content, const String& attributes) {
    return HtmlTag("textarea", content, attributes);
}

String HtmlSelect(const String& content, const String& attributes) {
    return HtmlTag("select", content, attributes);
}

String HtmlOption(const String& content, const String& attributes) {
    return HtmlTag("option", content, attributes);
}

String HtmlBr() {
    return HtmlSelfClosingTag("br");
}

String HtmlHr() {
    return HtmlSelfClosingTag("hr");
}
