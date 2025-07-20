#pragma once
#include "CommandSourceType.h"

struct CommandContext {
    CommandSourceType source = CommandSourceType::Unknown;
    String command;
    String argument;
};
