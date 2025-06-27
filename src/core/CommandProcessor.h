#pragma once
#include "CommandRegistry.h"

class CommandProcessor {
public:
    CommandProcessor(CommandRegistry& registry);
    void ProcessSerial();

private:
    CommandRegistry& registry;
};
