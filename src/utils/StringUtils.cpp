#include "StringUtils.h"

String StringUtils::ConvertByteUnits(double inputNumber, const String& inputFormat, const String& outputFormat, uint8_t outputDecimal, bool isOutputUnit) {
    const char* formats[] = { "B", "KB", "MB", "GB", "TB", "PB" };
    const int numFormats = sizeof(formats) / sizeof(formats[0]);

    auto getMultiplier = [&](const String& format) -> double {
        for (int i = 0; i < numFormats; i++) {
            if (format.equalsIgnoreCase(formats[i])) {
                return pow(1024, i);
            }
        }
        return 1; // default to bytes
    };

    double inputMultiplier = getMultiplier(inputFormat);
    double outputMultiplier = getMultiplier(outputFormat);

    double bytes = inputNumber * inputMultiplier;
    double outputValue = bytes / outputMultiplier;

    String result = String(outputValue, outputDecimal);
    if (isOutputUnit) {
        result += " " + outputFormat;
    }

    return result;
}
