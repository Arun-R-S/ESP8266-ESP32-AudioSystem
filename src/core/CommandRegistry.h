#pragma once
#include <Arduino.h>
#include <vector>

typedef bool (*CommandFunction)(const String &payload);

struct CommandEntry {
    const char* name;
    CommandFunction function;
};

class CommandRegistry {
public:
    void Register(const char* name, CommandFunction function);
    bool Execute(const String& name, const String& payload);

private:
    std::vector<CommandEntry> commands;
};
