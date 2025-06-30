#pragma once
#include <Arduino.h>
#include "../fields/HtmlTags.h"
#include "../fields/HtmlTagHelper.h"

// ✅ Build a Card
String HtmlCard(const String& title = "",
                const String& content = "",
                const String& footer = "",
                const String& cardAttributes = "");
