#pragma once
#include <Arduino.h>
#include "../fields/HtmlTags.h"
#include "../fields/HtmlTagHelper.h"
#include "../components/HtmlCard.h"

// 🔹 UI Block Functions
String HtmlPageHeader(const String& title, const String& subtitle = "");
String HtmlNavbar(const std::vector<std::pair<String, String>>& links);
String HtmlFooter(const String& content = "© 2025 MyDevice");
String HtmlContainer(const String& content, const String& attributes = "");
String HtmlSectionBlock(const String& content, const String& attributes = "");
