#include "StatusManager.h"
#include "Logger.h"
#include <map>

std::map<String, ComponentStatus> StatusManager::statusMap;

void StatusManager::Init() {
    statusMap.clear();
}

void StatusManager::SetError(const String& component, ErrorCode code) {
    ComponentStatus& status = statusMap[component];
    status.isValid = false;
    status.hasError = true;
    status.errorCode = code;

    AddLogError(component.c_str(), "Error occurred: %s", GetErrorMessage(code));
}

void StatusManager::ClearError(const String& component) {
    ComponentStatus& status = statusMap[component];
    status.isValid = true;
    status.hasError = false;
    status.errorCode = ERROR_NONE;
}

bool StatusManager::HasError(const String& component) {
    return statusMap[component].hasError;
}

bool StatusManager::IsValid(const String& component) {
    return statusMap[component].isValid;
}

ErrorCode StatusManager::GetErrorCode(const String& component) {
    return statusMap[component].errorCode;
}

const char* StatusManager::GetErrorMessage(ErrorCode code) {
    switch (code) {
        case ERROR_NONE: return "No Error";
        case ERROR_I2C_COMMUNICATION: return "I2C Communication Failed";
        case ERROR_EEPROM_READ_FAIL: return "EEPROM Read Failed";
        case ERROR_EEPROM_WRITE_FAIL: return "EEPROM Write Failed";
        case ERROR_DEVICE_NOT_FOUND: return "Device Not Found";
        case ERROR_INVALID_DATA: return "Invalid Data";
        case ERROR_UNKNOWN: return "Unknown Error";
        default: return "Unknown Error";
    }
}

void StatusManager::PrintStatus() {
    AddLogInfo("Status", "==== System Component Status ====");
    for (const auto& pair : statusMap) {
        const auto& name = pair.first;
        const auto& status = pair.second;

        AddLogInfo(name.c_str(), "Valid: %s | Error: %s | Code: %s",
               status.isValid ? "Yes" : "No",
               status.hasError ? "Yes" : "No",
               GetErrorMessage(status.errorCode));
    }
    AddLogInfo("Status", "=================================");
}
