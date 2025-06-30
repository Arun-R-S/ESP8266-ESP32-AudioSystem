#pragma once
#include <Arduino.h>
#include <map>

// ✅ Function to render template with placeholders replaced
String RenderTemplate(const String& templateStr, const std::map<String, String>& placeholders);

// ✅ Function to generate full HTML page template
String HtmlPageTemplate(const String& title, 
                         const String& bodyContent,
                         const String& headExtras = "",
                         const String& bodyExtras = "");
