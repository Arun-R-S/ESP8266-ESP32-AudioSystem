#pragma once

enum class WiFiState {
    DISCONNECTED,
    CONNECTING,
    CONNECTED,
    AP_MODE
};

class WiFiManager {
public:
    void begin();
    void handle();
    bool isConnected();
    WiFiState getState() { return state; }

private:
    bool connectToWiFi();
    void startAPMode();

    WiFiState state = WiFiState::DISCONNECTED;
    unsigned long connectStartTime = 0;
    const unsigned long connectTimeout = 15000; // 15 seconds
};
