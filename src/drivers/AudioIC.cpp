#include "AudioIC.h"

AudioIC::AudioIC() {}

bool AudioIC::begin() {
    Logger::info("AudioIC begin");

    // No real 'begin' needed for TDA7439, Wire.begin is already called.
    // Optionally set default values
    setVolume(currentVolume);
    setInput(currentInput);
    setBass(currentBass);
    setTreble(currentTreble);

    Logger::info("AudioIC initialized");
    return true;
}

void AudioIC::loadSettings() {
    Logger::info("Loading audio settings...");
    // Add EEPROM load logic if needed
    // For now, using defaults

        setVolume(currentVolume);
        setInput(currentInput);
        setBass(currentBass);
        setTreble(currentTreble);

       
}

void AudioIC::logSystemInfo() {
    Logger::info("Volume: %d", currentVolume);
    Logger::info("Input: %d", currentInput);
    Logger::info("Bass: %d", currentBass);
    Logger::info("Treble: %d", currentTreble);
}

void AudioIC::setVolume(uint8_t volume) {
    currentVolume = volume;
    tda.setVolume(volume);
    Logger::info("Volume set to %d", volume);
}

uint8_t AudioIC::getVolume() const {
    return currentVolume;
}

void AudioIC::setInput(uint8_t input) {
    currentInput = input;
    tda.setInput(input);
    Logger::info("Input set to %d", input);
}

uint8_t AudioIC::getInput() const {
    return currentInput;
}

void AudioIC::setBass(int8_t value) {
    currentBass = value;
    tda.setSnd(value, 1);
    Logger::info("Bass set to %d", value);
}

int8_t AudioIC::getBass() const {
    return currentBass;
}

void AudioIC::setTreble(int8_t value) {
    currentTreble = value;
    tda.setSnd(value, 3);
    Logger::info("Treble set to %d", value);
}

int8_t AudioIC::getTreble() const {
    return currentTreble;
}

void AudioIC::mute() {
    tda.mute();
    Logger::warning("Audio muted");
}
