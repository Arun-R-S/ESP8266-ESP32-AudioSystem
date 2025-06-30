#pragma once

enum class SupportedFeatures : uint16_t {
    None            = 0x0000,
    Loudness        = 0x0001,
    MasterVolume    = 0x0002,
    InputSelection  = 0x0003,
    BassControl     = 0x0004,
    TrebleControl   = 0x0005,
    MiddleControl   = 0x0006,
    BalanceControl  = 0x0007,
    FrontLeftVolume = 0x0008,
    FrontRightVolume= 0x0009,
    RearLeftVolume  = 0x0010,
    RearRightVolume = 0x0011,
    CenterVolume    = 0x0012,
    SubwooferVolume = 0x0012,
    // Add more like MuteControl, SoftMute, InputGain, etc.
};

inline SupportedFeatures operator|(SupportedFeatures a, SupportedFeatures b) {
    return static_cast<SupportedFeatures>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
}

inline SupportedFeatures operator&(SupportedFeatures a, SupportedFeatures b) {
    return static_cast<SupportedFeatures>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));
}

inline bool hasFeature(SupportedFeatures value, SupportedFeatures flag) {
    return (static_cast<uint16_t>(value) & static_cast<uint16_t>(flag)) != 0;
}
