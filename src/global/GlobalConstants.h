#pragma once
#include <Arduino.h>
#ifdef ESP8266

#else

#endif


class GlobalConstants {
public:
    static String softwareVersion;
    static String appName;
    static String webAppName;
};
