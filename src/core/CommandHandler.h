// src/core/CommandHandler.h
#pragma once
#include <WString.h>

class CommandHandler {
public:
    virtual bool CanHandle(const String& command) = 0;
    virtual String HandleCommand(const String& fullCommand) = 0;
};
