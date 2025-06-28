#pragma once

class DisplayUI {
public:
    static void Begin();
    static void ShowStatus();
    static void ShowVolume(int volume);
    static void ShowMenu(const char* menu);
};
