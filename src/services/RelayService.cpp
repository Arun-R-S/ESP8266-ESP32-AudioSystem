// src/services/RelayService.cpp
#include "RelayService.h"

bool RelayService::CanHandle(const String& command) {
    return command.startsWith("Power");
}

String RelayService::HandleCommand(const String& fullCommand) {
    // Examples:
    // Power1=1 => turn on relay 1
    // Power2 => get status of relay 2
    // Power => return all relays status

    int relayIndex = 0;
    bool isSet = fullCommand.indexOf('=') != -1;

    String cmd = fullCommand;
    String value = "";

    if (isSet) {
        cmd = fullCommand.substring(0, fullCommand.indexOf('='));
        value = fullCommand.substring(fullCommand.indexOf('=') + 1);
    }

    if (cmd.length() > 5) {
        relayIndex = cmd.substring(5).toInt();  // Power1 -> 1
    }

    if (isSet) {
        // Simulate relay ON/OFF
        // RelayManager::SetRelay(relayIndex, value == "1");
        return "Relay" + String(relayIndex) + " set to " + value;
    } else {
        // return "Relay" + String(relayIndex) + " is ON/OFF"
        return "Relay" + String(relayIndex) + " is ON";
    }
}
