#pragma once

#include "CommandSourceType.h"
#include <WString.h>

class CommandRequest {
public:
    CommandRequest(CommandSourceType source, const String& raw) : source(source), rawCommand(raw) {}

    CommandSourceType GetSource() const { return source; }
    String GetRawCommand() const { return rawCommand; }

private:
    CommandSourceType source;
    String rawCommand;
};