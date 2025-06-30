#pragma once
#include <Arduino.h>
#include <vector>
#include "../fields/HtmlTags.h"      // ✅ Use tag builder
#include "../fields/HtmlTagHelper.h" // ✅ Use atomic helpers

// ✅ A Form Field Structure
struct HtmlField {
    String label;
    String tagHtml;
    String description;
};

// ✅ Build a form row with label + field + description
String HtmlFormRow(const HtmlField& field);

// ✅ Build a complete form from a list of fields
String HtmlFormBuilder(const std::vector<HtmlField>& fields,
                        const String& action,
                        const String& method = "post",
                        const String& formAttributes = "");
