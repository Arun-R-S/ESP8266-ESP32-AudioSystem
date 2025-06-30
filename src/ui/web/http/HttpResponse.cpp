#include "HttpResponse.h"

HttpResponse::HttpResponse(AsyncWebServerRequest *req) {
    request = req;
}

void HttpResponse::SendHTML(const String& html, int statusCode) {
    request->send(statusCode, "text/html", html);
}

void HttpResponse::SendJSON(const String& json, int statusCode) {
    request->send(statusCode, "application/json", json);
}

void HttpResponse::SendText(const String& text, int statusCode) {
    request->send(statusCode, "text/plain", text);
}

void HttpResponse::Redirect(const String& location) {
    request->redirect(location);
}

void HttpResponse::SendError(int code, const String& message) {
    request->send(code, "text/plain", "Error " + String(code) + ": " + message);
}
