#pragma once

#include <WString.h>

class CommandResponse {
public:
    void SetResponse(const String& resp) { response = resp; }
    const String& GetResponse() const { return response; }

private:
    String response;
};
