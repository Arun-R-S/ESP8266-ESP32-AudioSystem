#include "HtmlTemplate.h"

// 🔥 RenderTemplate — replaces {{PLACEHOLDER}} with actual content
String RenderTemplate(const String& templateStr, const std::map<String, String>& placeholders) {
    String result = templateStr;
    for (const auto& item : placeholders) {
        result.replace("{{" + item.first + "}}", item.second);
    }
    return result;
}

String GetLiveScript()
{
    return R"rawliteral(

function updateLiveStatus(interval = 2000) {
    async function fetchAndUpdate() {
        const elements = document.querySelectorAll('[livestatuscmd]');
        const cmds = [];

        // Collect commands
        elements.forEach(el => {
            const cmd = el.getAttribute('livestatuscmd');
            if (cmd) cmds.push(cmd);
        });

        if (cmds.length === 0) {
            scheduleNext();
            return;
        }

        const query = cmds.map(cmd => {
            const [key, value] = cmd.split('=');
            return `${encodeURIComponent(key)}=${encodeURIComponent(value)}`;
        }).join('&');
        const url = `/stat?${query}`;

        try {
            const response = await fetch(url);
            const html = await response.text();

            const tempDiv = document.createElement('div');
            tempDiv.innerHTML = html;

            const newElements = tempDiv.querySelectorAll('[livestatuscmd]');
            newElements.forEach(newEl => {
                const cmd = newEl.getAttribute('livestatuscmd');
                const target = document.querySelector(`[livestatuscmd="${cmd}"]`);
                if (target) {
                    target.innerHTML = newEl.innerHTML;
                }
            });
        } catch (err) {
            console.error('LiveStatus update failed:', err);
        }

        scheduleNext(); // Schedule next only after previous finishes
    }

    function scheduleNext() {
        setTimeout(fetchAndUpdate, interval);
    }

        fetchAndUpdate(); 
}
    document.addEventListener('DOMContentLoaded', () => {
        updateLiveStatus(2000); // Start first call
    });

)rawliteral";
}

String getBootstrapCss()
{
    return R"rawliteral(
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.7/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-LN+7fdVzj6u52u30Kp6M/trliBMCMKTyK833zpbD+pXdCLuTusPj697FH4R/5mcr" crossorigin="anonymous">
    )rawliteral";
}

String getBootstrapScript(){
    return R"rawliteral(
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.7/dist/js/bootstrap.bundle.min.js" integrity="sha384-ndDqU0Gzau9qJ1lfW4pNLlhNTkCfHzAVBReH9diLvGRem5+R9g2FzA8ZGN954O5Q" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.11.8/dist/umd/popper.min.js" integrity="sha384-I7E8VVD/ismYTF4hNIPjVp/Zjvgyol6VFvRkX/vR+Vc4jQkC+hVqc2pM8ODewa9r" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.7/dist/js/bootstrap.min.js" integrity="sha384-7qAoOXltbVP82dhxHAUje59V5r2YsVfBafyUDxEdApLPmcdhBPg1DKg1ERo0BZlK" crossorigin="anonymous"></script>
    )rawliteral";
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
            "{{HEAD_BOOTSTRAP_CSS}}"
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
            "<script>"
            "{{BODY_SCRIPT}}"
            "</script>"
            "{{BODY_BOOTSTRAP_SCRIPT}}"
        "</body>"
        "</html>";

    return RenderTemplate(tpl, {
        {"TITLE", title},
        {"BODY_CONTENT", bodyContent},
        {"HEAD_EXTRAS", headExtras},
        {"BODY_EXTRAS", bodyExtras},
        {"BODY_SCRIPT", GetLiveScript()},
        {"HEAD_BOOTSTRAP_CSS", getBootstrapCss()},
        {"BODY_BOOTSTRAP_SCRIPT", getBootstrapScript()}
    });
}
