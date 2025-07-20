#pragma once

#include "ParsedCommand.h"
#include "CommandRequest.h"
#include "CommandResponse.h"
#include <functional>
#include <map>
#include <vector>
#include "ParseFullCommand.h"

using CommandCallback = std::function<void(const ParsedCommand&, CommandResponse&)>;

class CommandHandlerManager {
public:
    static CommandHandlerManager& Instance() {
        static CommandHandlerManager instance;
        return instance;
    }

    void RegisterCommand(const String& commandName, CommandCallback callback) {
        handlers[commandName] = callback;
    }

    void HandleRequest(const CommandRequest& request, CommandResponse& response) {
        auto commands = ParseFullCommand::Parse(request.GetRawCommand());
        for (const auto& cmd : commands) {
            auto it = handlers.find(cmd.GetName());
            if (it != handlers.end()) {
                it->second(cmd, response);
            } else {
                response.SetResponse("Unknown command: " + cmd.GetName());
            }
        }
    }

private:
    std::map<String, CommandCallback> handlers;
};