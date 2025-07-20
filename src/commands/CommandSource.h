#pragma once

#include <WString.h>

enum class CommandSource {
    Serial,
    WebGet,
    WebApi,
    Telnet,
    Unknown
};