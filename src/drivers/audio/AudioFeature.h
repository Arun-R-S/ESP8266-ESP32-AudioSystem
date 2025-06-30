#pragma once

#include <stdint.h>

enum class AudioFeature : uint16_t {
    None        = 0,
    Volume      = 1 << 0,
    Bass        = 1 << 1,
    Treble      = 1 << 2,
    Balance     = 1 << 3,
    Loudness    = 1 << 4,
    Input       = 1 << 5,
    Middle      = 1 << 6,
    Subwoofer   = 1 << 7,
    Mute        = 1 << 8,
    FrontLeft   = 1 << 9,
    FrontRight  = 1 << 10,
    RearLeft    = 1 << 11,
    RearRight   = 1 << 12,
    Center      = 1 << 13
};

// Bitwise operators
inline AudioFeature operator|(AudioFeature a, AudioFeature b) {
    return static_cast<AudioFeature>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
}
inline AudioFeature operator&(AudioFeature a, AudioFeature b) {
    return static_cast<AudioFeature>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));
}
inline AudioFeature& operator|=(AudioFeature& a, AudioFeature b) {
    a = a | b;
    return a;
}
inline bool hasFeature(AudioFeature value, AudioFeature flag) {
    return (static_cast<uint16_t>(value) & static_cast<uint16_t>(flag)) != 0;
}
