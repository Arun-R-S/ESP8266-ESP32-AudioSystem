#include "HtmlTagHelper.h"
#include <regex>
#include <sstream>

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

static String UpdateAttribute(const String& html, const String& attr, const String& value, bool append) {
    std::string result = html.c_str();
    std::regex tagRegex(R"(<(\w+)([^>]*)>)");
    std::smatch match;

    if (std::regex_search(result, match, tagRegex)) {
        std::string tagName = match[1];
        std::string attrString = match[2];

        std::string pattern = attr.c_str();
        pattern += "=\"([^\"]*)\"";
        std::regex attrRegex(pattern);
        std::smatch attrMatch;

        std::string updatedAttr;
        bool found = std::regex_search(attrString, attrMatch, attrRegex);
        if (found) {
            // Attribute found
            std::string currentValue = attrMatch[1];
            std::set<std::string> values;
            std::istringstream iss(currentValue);
            for (std::string s; iss >> s;) values.insert(s);

            if (append) {
                values.insert(value.c_str());
            } else {
                values.erase(value.c_str());
            }

            std::ostringstream oss;
            for (const auto& v : values) oss << v << " ";
            std::string newValue = oss.str();
            newValue = std::regex_replace(newValue, std::regex(R"(\s+$)"), std::string("")); //Trim

            updatedAttr = std::string(attr.c_str()) + "=\"" + newValue + "\"";
            attrString = std::regex_replace(attrString, attrRegex, updatedAttr);
        } else if (append) {
            // Attribute not found, append it
            updatedAttr = " " + std::string(attr.c_str()) + "=\"" + std::string(value.c_str()) + "\"";
            attrString += updatedAttr;
        }

        std::string newTag = "<" + tagName + attrString + ">";
        result = std::regex_replace(result, tagRegex, newTag, std::regex_constants::format_first_only);
    }

    return String(result.c_str());
}

String HtmlAttrAppend(const String& html, const String& attr, const String& value) {
    return UpdateAttribute(html, attr, value, true);
}

String HtmlAttrRemove(const String& html, const String& attr, const String& value) {
    return UpdateAttribute(String(html.c_str()), attr, value, false);
}

String HtmlAttrsAppend(const String& html, std::vector<std::pair<String, String>>& attrs) {
    String result = html;
    for (size_t i = 0; i < attrs.size(); ++i)
    {
        const String &attr = attrs[i].first;
        const String &value = attrs[i].second;
        result = HtmlAttrAppend(result, attr, value);
    }
    return result;
}

String HtmlAttrsRemove(const String& html, std::vector<std::pair<String, String>>& attrs) {
    String result = String(html.c_str());
    for (size_t i = 0; i < attrs.size(); ++i)
    {
        const String &attr = attrs[i].first;
        const String &value = attrs[i].second;
        result = HtmlAttrRemove(result, attr, value);
    }
    return result;
}