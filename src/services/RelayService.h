// src/services/RelayService.h
#pragma once
#include "core/CommandHandler.h"

class RelayService : public CommandHandler {
public:
    bool CanHandle(const String& command) override;
    String HandleCommand(const String& fullCommand) override;
};
