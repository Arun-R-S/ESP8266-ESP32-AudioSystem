#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>

class HttpResponse {
public:
    AsyncWebServerRequest *request;

    HttpResponse(AsyncWebServerRequest *req);

    void SendHTML(const String& html, int statusCode = 200);
    void SendHTMLWithPreBuiltTags(const String& html, int statusCode = 200);
    void SendJSON(const String& json, int statusCode = 200);
    void SendText(const String& text, int statusCode = 200);
    void Redirect(const String& location);
    void SendError(int code, const String& message);
};
