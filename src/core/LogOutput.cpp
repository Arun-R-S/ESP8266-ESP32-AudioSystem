#include <Arduino.h>

class LogOutput {
public:
    virtual void Print(const char* msg) = 0;
};

class SerialLogOutput : public LogOutput {
public:
    void Print(const char* msg) override {
        Serial.println(msg);
    }
};
