#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <map>

class HttpRequest {
public:
    AsyncWebServerRequest *request;

    HttpRequest(AsyncWebServerRequest *req);

    String Method();
    String Path();
    String GetParam(const String& name, const String& defaultValue = "");
    std::map<String, String> GetParams();

    bool IsPost();
    bool IsGet();
};
