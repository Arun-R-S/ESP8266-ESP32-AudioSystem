#pragma once

#include <Arduino.h>

class ResponseManager {
public:
    static void Clear();
    static void Append(const char* format, ...);
    static const char* Get();
    static bool IsEmpty();

private:
    static String buffer;
};
