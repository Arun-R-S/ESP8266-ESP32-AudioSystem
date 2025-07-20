#include "CommandHandlerManager.h"

void RegisterCoreCommands() {
    CommandHandlerManager::Instance().RegisterCommand("Power", [](const ParsedCommand& cmd, CommandResponse& res) {
        if (cmd.GetValue().isEmpty()) {
            res.SetResponse("Power: 0,1,1"); // Dummy all switch state
        } else {
            res.SetResponse("Power set to: " + cmd.GetValue());
        }
    });

    CommandHandlerManager::Instance().RegisterCommand("Status", [](const ParsedCommand& cmd, CommandResponse& res) {
        res.SetResponse("System Status: OK");
    });
}
