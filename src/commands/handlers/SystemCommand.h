#pragma once

#include "services/SystemService.h"
#include "commands/CommandContext.h"

class SystemCommand {
public:
    static String UpTime(const CommandContext& context);
};
