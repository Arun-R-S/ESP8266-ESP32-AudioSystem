#pragma once

enum class CommandSourceType {
    Unknown,
    Serial,
    Telnet,
    WebRequest,     // HTML
    WebApi,         // JSON
    Internal
};
