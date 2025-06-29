#pragma once

#include <Arduino.h>
#include <map>

enum ErrorCode {
    ERROR_NONE = 0,
    ERROR_I2C_COMMUNICATION = 1,
    ERROR_EEPROM_READ_FAIL,
    ERROR_EEPROM_WRITE_FAIL,
    ERROR_DEVICE_NOT_FOUND,
    ERROR_INVALID_DATA,
    ERROR_DRIVER_INIT_FAILED,

    //Add the future ErrorCodes here [START]

    //Add the future ErrorCodes here [END]

    ERROR_UNKNOWN = 255
};

struct ComponentStatus {
    bool isValid = true;
    bool hasError = false;
    ErrorCode errorCode = ERROR_NONE;
};

class StatusManager {
public:
    static void Init();

    static void SetError(const String& component, ErrorCode code);
    static void ClearError(const String& component);

    static bool HasError(const String& component);
    static bool IsValid(const String& component);
    static ErrorCode GetErrorCode(const String& component);
    static const char* GetErrorMessage(ErrorCode code);

    static void PrintStatus(); // Print to Serial, LCD, etc.

private:
    static std::map<String, ComponentStatus> statusMap;
};
