#pragma once

#include "CommandSource.h"
#include <WString.h>

class CommandRequest {
public:
    CommandRequest(CommandSource source, const String& raw) : source(source), rawCommand(raw) {}

    CommandSource GetSource() const { return source; }
    String GetRawCommand() const { return rawCommand; }

private:
    CommandSource source;
    String rawCommand;
};