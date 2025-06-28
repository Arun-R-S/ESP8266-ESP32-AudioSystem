#include "ResponseManager.h"

String ResponseManager::buffer = "";

void ResponseManager::Clear() {
    buffer = "";
}

void ResponseManager::Append(const char* format, ...) {
    char temp[256]; // Adjust buffer size as needed
    va_list args;
    va_start(args, format);
    vsnprintf(temp, sizeof(temp), format, args);
    va_end(args);
    buffer += temp;
}

const char* ResponseManager::Get() {
    return buffer.c_str();
}

bool ResponseManager::IsEmpty() {
    return buffer.length() == 0;
}
