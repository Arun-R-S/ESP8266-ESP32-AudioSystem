#pragma once

enum class AudioFeature : uint16_t {
    None        = 0,
    Volume      = 1 << 0,
    Bass        = 1 << 1,
    Treble      = 1 << 2,
    Middle      = 1 << 3,
    Loudness    = 1 << 4,
    Balance     = 1 << 5,
    Subwoofer   = 1 << 6,
    Fader       = 1 << 7,
    InputSelect = 1 << 8
};

// Operators to handle bit flags
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
    return (value & flag) == flag;
}
