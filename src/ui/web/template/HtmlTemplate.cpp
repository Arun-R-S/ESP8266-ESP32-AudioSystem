#include "HtmlTemplate.h"

// 🔥 RenderTemplate — replaces {{PLACEHOLDER}} with actual content
String RenderTemplate(const String& templateStr, const std::map<String, String>& placeholders) {
    String result = templateStr;
    for (const auto& item : placeholders) {
        result.replace("{{" + item.first + "}}", item.second);
    }
    return result;
}

// 🔥 HtmlPageTemplate — wraps content in full HTML page
String HtmlPageTemplate(const String& title, 
                         const String& bodyContent,
                         const String& headExtras,
                         const String& bodyExtras) {
    String tpl = 
        "<!DOCTYPE html>"
        "<html>"
        "<head>"
            "<meta charset='UTF-8'>"
            "<meta name='viewport' content='width=device-width, initial-scale=1'>"
            "<title>{{TITLE}}</title>"
            "{{HEAD_EXTRAS}}"
            "<style>"
                "body{font-family:sans-serif;margin:0;padding:10px;}"
                ".container{max-width:800px;margin:auto;}"
                ".navbar{background:#eee;padding:5px;margin-bottom:15px;}"
                ".nav-link{margin-right:10px;text-decoration:none;color:#333;}"
                ".nav-link:hover{text-decoration:underline;}"
                ".card{border:1px solid #ddd;border-radius:8px;padding:10px;margin:10px 0;background:#fff;box-shadow:2px 2px 5px #ccc;}"
                ".card-header{font-weight:bold;margin-bottom:8px;}"
                ".card-footer{border-top:1px solid #ddd;margin-top:8px;padding-top:6px;font-size:0.9em;color:#555;}"
                ".page-header{margin-bottom:20px;}"
                ".footer{border-top:1px solid #ccc;padding-top:5px;font-size:0.8em;color:#555;}"
            "</style>"
        "</head>"
        "<body {{BODY_EXTRAS}}>"
            "{{BODY_CONTENT}}"
        "</body>"
        "</html>";

    return RenderTemplate(tpl, {
        {"TITLE", title},
        {"BODY_CONTENT", bodyContent},
        {"HEAD_EXTRAS", headExtras},
        {"BODY_EXTRAS", bodyExtras}
    });
}
