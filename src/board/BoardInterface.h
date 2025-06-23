#pragma once

class BoardInterface {
public:
    virtual void setupI2C() = 0;
    virtual void setupWiFi() = 0;
    virtual const char* getBoardName() = 0;
    virtual int getDefaultSDA() = 0;
    virtual int getDefaultSCL() = 0;
    virtual ~BoardInterface() {}
};
