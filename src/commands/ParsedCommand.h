#pragma once

#include <WString.h>

class ParsedCommand {
public:
    ParsedCommand(const String& name, const String& value) : name(name), value(value) {}

    const String& GetName() const { return name; }
    const String& GetValue() const { return value; }

private:
    String name;
    String value;
};