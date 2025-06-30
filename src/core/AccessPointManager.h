#pragma once

class AccessPointManager {
public:
    void start();
    void stop();
    bool isActive() { return active; }

private:
    bool active = false;
};
