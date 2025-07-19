#pragma once
#include <Arduino.h>

class SystemElements{
public:
    static String UpTime(bool isLiveElement);
    static String RamUsage(bool isLiveElement);
};