#pragma once
#include <cstdint>

struct Config {
    uint8_t i2c_sda_pin;
    uint8_t i2c_scl_pin;
    uint8_t audio_ic_addr;
    uint8_t input_select_pin;
    uint8_t volume_up_pin;
    uint8_t volume_down_pin;
    uint8_t loudness_toggle_pin;
    // Add more config as needed

    void Load();
    void Save();
};
