#include "CommandProcessor.h"
#include "Logger.h"

CommandProcessor::CommandProcessor(CommandRegistry& reg) : registry(reg) {}

std::vector<CommandHandler*> CommandProcessor::handlers;

void CommandProcessor::RegisterHandler(CommandHandler* handler) {
    handlers.push_back(handler);
}

String CommandProcessor::ExecuteCommand(const String& command) {
    for (auto* handler : handlers) {
        if (handler->CanHandle(command)) {
            return handler->HandleCommand(command);
        }
    }
    return "Unknown command";
}

void CommandProcessor::ProcessSerial() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();

        if (input.length() == 0) return;

        int spaceIndex = input.indexOf(' ');
        String cmd = input;
        String payload = "";

        if (spaceIndex != -1) {
            cmd = input.substring(0, spaceIndex);
            payload = input.substring(spaceIndex + 1);
        }

        AddLogDebug("Serial", "Command='%s' Payload='%s'", cmd.c_str(), payload.c_str());
        registry.Execute(cmd, payload);
    }
}
