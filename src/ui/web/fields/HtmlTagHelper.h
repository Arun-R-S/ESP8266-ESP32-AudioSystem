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

