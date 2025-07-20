#include "SystemCommand.h"
#include "ui/web/fields/HtmlTags.h"

String SystemCommand::UpTime(const CommandContext& context) {
    String formatted = SystemService::GetFormattedUptime();
    uint32_t seconds = SystemService::GetUptimeSeconds();

    switch (context.source) {
        case CommandSourceType::Serial:
        case CommandSourceType::Telnet:
        case CommandSourceType::Internal:
            return "Uptime: " + formatted;

        case CommandSourceType::WebRequest:
            return HtmlSpan(formatted);

        case CommandSourceType::WebApi: {
            String json = "{";
            json += "\"uptime\":\"" + formatted + "\",";
            json += "\"seconds\":" + String(seconds);
            json += "}";
            return json;
        }

        default:
            return formatted;
    }
}
