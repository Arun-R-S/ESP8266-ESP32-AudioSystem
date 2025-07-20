#pragma once
#include <Arduino.h>
#include <vector>

// ✅ Build a single HTML attribute
String HtmlAttr(const String& key, const String& value);

// ✅ Combine multiple attributes into a single string
String HtmlAttrs(const std::vector<std::pair<String, String>>& attributes);

// ✅ Build any HTML tag (generic)
String HtmlTag(const String& tagName, const String& content = "", const String& attributes = "");

// ✅ Self-closing version for tags like <input>, <br>, <hr>, <meta>
String HtmlSelfClosingTag(const String& tagName, const String& attributes = "");

// ✅ Append an Attribute and value to the provided html string
String HtmlAttrAppend(const String& html, const String& attr, const String& value);

// ✅ Append list of Attributes and values to the provided html string
String HtmlAttrsAppend(const String& html, std::vector<std::pair<String, String>>& attrs);

// ✅ Remove an Attribute and value from the provided html string
String HtmlAttrRemove(const std::string& html, const std::string& attr, const std::string& value);

// ✅ Remove list of Attribute and value from the provided html string
String HtmlAttrsRemove(const std::string& html, std::vector<std::pair<String, String>>& attrs);