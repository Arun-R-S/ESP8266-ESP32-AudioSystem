#include "HttpRequest.h"

HttpRequest::HttpRequest(AsyncWebServerRequest *req) {
    request = req;
}

String HttpRequest::Method() {
    return request->methodToString();
}

String HttpRequest::Path() {
    return request->url();
}

String HttpRequest::GetParam(const String& name, const String& defaultValue) {
    if (request->hasParam(name, true)) {
        return request->getParam(name, true)->value();
    }
    return defaultValue;
}

std::map<String, String> HttpRequest::GetParams() {
    std::map<String, String> params;
    int count = request->params();
    for (int i = 0; i < count; i++) {
        const AsyncWebParameter* p = request->getParam(i);
        params[p->name()] = p->value();
    }
    return params;
}

bool HttpRequest::IsPost() {
    return request->method() == HTTP_POST;
}

bool HttpRequest::IsGet() {
    return request->method() == HTTP_GET;
}
