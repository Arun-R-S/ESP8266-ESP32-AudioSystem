
# ESP8266 / ESP32 Audio System Controller

![License](https://img.shields.io/github/license/Arun-R-S/ESP8266-ESP32-AudioSystem?logo=unlicense&color=red&label=License) ![Stars](https://img.shields.io/github/stars/Arun-R-S/ESP8266-ESP32-AudioSystem) ![Issues](https://img.shields.io/github/issues/Arun-R-S/ESP8266-ESP32-AudioSystem?logo=sanfranciscomunicipalrailway&label=Issues) ![Release](https://img.shields.io/github/v/release/Arun-R-S/ESP8266-ESP32-AudioSystem?logo=codeblocks&label=Release)  ![Downloads](https://img.shields.io/github/downloads/Arun-R-S/ESP8266-ESP32-AudioSystem/total?logo=abdownloadmanager&label=Downloads) ![PlatformIO](https://img.shields.io/badge/PlatformIO-Compatible-orange?logo=platformio) ![Arduino](https://img.shields.io/badge/Arduino-Compatible-blue?logo=arduino)

![Contributions Welcome](https://img.shields.io/badge/a_t-Welcome-blue?logo=contabo&label=Contributions) 
## 🔥 Overview

This project is a highly modular, configurable, and extensible firmware for ESP8266/ESP32 microcontrollers designed to control audio ICs like **TDA7439**, **PT2313**, **PT2322**, and others via I2C. It features support for physical button control, LCD displays, web UI (future), EEPROM/Flash settings storage, and preset management — all following clean architecture, SOLID principles, and professional coding practices.

## 🎯 Features

- ✅ **Audio IC Control**
  - Volume, Bass, Treble, Balance, Loudness, Input Selection
- ✅ **Hardware Abstraction Layer (HAL)**
  - Abstracts I2C, EEPROM, Logging, Display, etc.
- ✅ **Drivers Layer**
  - Drivers for audio ICs (e.g., TDA7439) with clean APIs
- ✅ **UI/UX Support**
  - Physical buttons and 16x2 I2C LCD
  - Future-proof for Web UI
- ✅ **Configuration Management**
  - No hardcoded pins, fully configurable
  - Settings stored in EEPROM/Flash with CRC validation
- ✅ **Presets Management**
  - Save and switch multiple audio presets
- ✅ **Centralized Logging**
  - Supports different log levels with tagged logs
- ✅ **Error Handling**
  - Error codes, retries, fallback handling for I2C failures
- ✅ **Cross-Platform Support**
  - Works with both **ESP8266** and **ESP32**
- ✅ **Tasmota-like Storage System**
  - Binary data storage with integrity checks

## 📁 Folder Structure

```plaintext
ESP8266-ESP32-AudioSystem/
│
├── boards/            → Board-specific configurations
├── config/            → Default and custom configurations
├── core/              → Core logic (SettingsManager, Logger, I2CManager)
├── drivers/
│   └── audio/         → Audio IC drivers (e.g., TDA7439.cpp)
├── filesystem/        → Persistent storage handling (EEPROM/Flash)
├── hal/               → Hardware Abstraction Layer (I2C, Display, etc.)
├── presets/           → Preset management (save, load)
├── services/          → Business logic services (AudioService, etc.)
├── ui/
│   ├── display/       → LCD UI
│   └── web/           → Future Web UI
├── utils/             → Utilities (CRC, helpers)
├── include/           → Header files
├── src/               → Main application entry point
├── platformio.ini     → PlatformIO build configuration
└── README.md          → This file
```

## ⚙️ Supported Hardware

| Microcontroller | Supported |
|-----------------|------------|
| ESP8266 (NodeMCU, Wemos D1) | ✅ |
| ESP32 (DevKit, Wroom, Wrover) | ✅ |

| Audio IC         | Status |
|------------------|--------|
| TDA7439          | ✅ Complete |
| PT2313           | 🔜 Planned |
| PT2322           | 🔜 Planned |

| UI               | Status |
|------------------|--------|
| 16x2 LCD (I2C)   | 🔜 (Planned) |
| Web UI           | 🔜 (Planned) |
| Push Buttons     | 🔜 (Planned) |

## 🚀 Getting Started

### 🛠 Prerequisites

- PlatformIO with VSCode (Recommended)
- ESP8266 or ESP32 board
- Audio IC (e.g., TDA7439) wired over I2C
- Optional: 16x2 I2C LCD Display, push buttons

### 📥 Installation

1. Clone the repo:

```bash
git clone https://github.com/Arun-R-S/ESP8266-ESP32-AudioSystem.git
cd ESP8266-ESP32-AudioSystem
```

2. Install dependencies via PlatformIO (auto resolves).

3. Edit `platformio.ini` to select your board.

4. Configure pins and settings:

```cpp
// config/BoardConfig.h

#define I2C_SDA_PIN  D2
#define I2C_SCL_PIN  D1
#define LCD_ADDRESS  0x27
#define AUDIO_I2C_ADDRESS 0x44
```

### 🔥 Build & Upload

- Build and upload:

```bash
pio run --target upload
```

- Open serial monitor:

```bash
pio device monitor
```

## 🎨 Example Usage

- Adjust Volume:

```cpp
AudioService.SetVolume(10);
```

- Change Bass:

```cpp
AudioService.SetBass(5);
```

- Switch Input:

```cpp
AudioService.SetInput(2);
```

- Save Preset:

```cpp
PresetManager.SavePreset(1);
```

- Load Preset:

```cpp
PresetManager.LoadPreset(1);
```

## 📝 Configuration Example

```cpp
// config/SettingsStruct.h

struct AudioSettings {
    uint8_t volume;
    uint8_t bass;
    uint8_t treble;
    uint8_t balance;
    bool loudness;
    uint8_t inputSource;
};
```

## 🔧 Settings Storage (Like Tasmota)

- Settings are stored in Flash/EEPROM with CRC32 validation.
- On corruption, factory defaults are restored.
- Supports versioning for future updates.

## 🚦 Logging System

- Log Levels: `DEBUG`, `INFO`, `WARN`, `ERROR`
- Usage:

```cpp
Logger(INFO, "Audio", "Volume set to %d", volume);
```

## 💡 Error Handling

- Retry mechanism on I2C failures.
- Return error codes for hardware failures.
- Fallback to defaults if storage fails.

## 🛡️ Coding Principles

- ✅ Clean Code
- ✅ SOLID Principles
- ✅ No hardcoded pins — fully configurable
- ✅ Modular architecture
- ✅ Separation of concerns
- ✅ Extensible for new ICs, UIs, or features

## 🏗️ Architecture Diagram

```plaintext
+------------------------+
|       Main App         |
+-----------+------------+
            ↓
+-----------+------------+
|         Services        |
+-----------+------------+
            ↓
+------+    +------+    +------+
| HAL  |    | Drivers|  | UI   |
+------+    +------+    +------+
            ↓
       +-----------+
       | Hardware   |
       +-----------+
```

## 🗺️ Roadmap

- [x] TDA7439 Driver
- [ ] LCD + Button UI
- [ ] Web UI Interface
- [ ] PT2313 and PT2322 Drivers
- [ ] MQTT/HTTP API
- [ ] OTA Update Support

## 🤝 Contribution

Contributions are welcome!

1. Fork this repository
2. Create your feature branch (`git checkout -b feature/awesome`)
3. Commit your changes (`git commit -m 'Add awesome feature'`)
4. Push to the branch (`git push origin feature/awesome`)
5. Open a Pull Request

## 🛂 Contributors
![Contributors](https://img.shields.io/github/contributors/user/repo)

## 📜 License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.

## 💖 Acknowledgements

- Inspired by Tasmota's robust configuration and storage mechanism.
- Thanks to the open-source community for drivers and libraries.

---

## 🚀 Let's Build Something Awesome Together!

---

### ⭐ If you like this project, don’t forget to **star** it on GitHub!
