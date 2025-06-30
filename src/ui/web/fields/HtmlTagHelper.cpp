#include "HtmlTagHelper.h"

// ✅ Build a single key='value' attribute
String HtmlAttr(const String& key, const String& value) {
    return key + "='" + value + "'";
}

// ✅ Combine multiple attributes into a string
String HtmlAttrs(const std::vector<std::pair<String, String>>& attributes) {
    String result = "";
    for (const auto& attr : attributes) {
        if (result.length()) result += " ";
        result += HtmlAttr(attr.first, attr.second);
    }
    return result;
}

// ✅ Generic tag builder
String HtmlTag(const String& tagName, const String& content, const String& attributes) {
    String html = "<" + tagName;
    if (attributes.length()) {
        html += " " + attributes;
    }
    html += ">" + content + "</" + tagName + ">";
    return html;
}

// ✅ Self-closing tag for input, br, hr, meta, etc.
String HtmlSelfClosingTag(const String& tagName, const String& attributes) {
    String html = "<" + tagName;
    if (attributes.length()) {
        html += " " + attributes;
    }
    html += ">";
    return html;
}
