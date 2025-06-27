#include "CommandRegistry.h"
#include "Logger.h"

void CommandRegistry::Register(const char* name, CommandFunction function) {
    commands.push_back({name, function});
}

bool CommandRegistry::Execute(const String& name, const String& payload) {
    for (const auto& cmd : commands) {
        if (name.equalsIgnoreCase(cmd.name)) {
            return cmd.function(payload);
        }
    }
    AddLogWarn("Command", "Unknown command '%s'", name.c_str());
    return false;
}
