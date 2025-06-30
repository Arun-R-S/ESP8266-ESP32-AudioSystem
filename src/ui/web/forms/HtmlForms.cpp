#include "HtmlForms.h"

// ✅ Form Row: label + field + (optional) description
String HtmlFormRow(const HtmlField& field) {
    String row = "";

    if (field.label.length()) {
        row += HtmlLabel(field.label, HtmlAttrs({{"class", "form-label"}}));
    }

    row += HtmlDiv(field.tagHtml, HtmlAttrs({{"class", "form-field"}}));

    if (field.description.length()) {
        row += HtmlDiv(field.description, HtmlAttrs({{"class", "form-desc"}}));
    }

    return HtmlDiv(row, HtmlAttrs({{"class", "form-row"}}));
}


// ✅ Full Form: builds the complete form
String HtmlFormBuilder(const std::vector<HtmlField>& fields,
                        const String& action,
                        const String& method,
                        const String& formAttributes) {
    String formBody = "";

    for (const auto& field : fields) {
        formBody += HtmlFormRow(field);
    }

    return HtmlForm(formBody,
                    HtmlAttrs({
                        {"action", action},
                        {"method", method}
                    }) + (formAttributes.length() ? " " + formAttributes : ""));
}
