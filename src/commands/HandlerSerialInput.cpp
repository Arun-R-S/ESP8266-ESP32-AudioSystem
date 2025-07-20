#include "CommandHandlerManager.h"
#include "CommandRequest.h"
#include "CommandResponse.h"
#include "CommandSource.h"
#include <Arduino.h>

void HandleSerialInput(const String& input) {
    CommandRequest request(CommandSource::Serial, input);
    CommandResponse response;
    CommandHandlerManager::Instance().HandleRequest(request, response);

    Serial.println(response.GetResponse());
}