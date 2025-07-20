#pragma once
#include "CommandRegistry.h"
#include "CommandHandler.h"

class CommandProcessor {
public:
    CommandProcessor(CommandRegistry& registry);
    void ProcessSerial();
    static void RegisterHandler(CommandHandler* handler);
    static String ExecuteCommand(const String& command);

private:
    CommandRegistry& registry;
    static std::vector<CommandHandler*> handlers;
};
