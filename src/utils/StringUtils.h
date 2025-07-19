 
#pragma once
#include <Arduino.h>

class StringUtils{
public:
    static String ConvertByteUnits(double inputNumber, const String& inputFormat, const String& outputFormat, uint8_t outputDecimal = 2, bool isOutputUnit = true);
};
