# PeripheralOS

![Version](https://img.shields.io/badge/version-v0.1.0--alpha-blue)
![Status](https://img.shields.io/badge/status-early%20development-orange)
![Linux](https://img.shields.io/badge/Linux-Alpha-success)
![Windows](https://img.shields.io/badge/Windows-Planned-lightgrey)
![macOS](https://img.shields.io/badge/macOS-Planned-lightgrey)
![C++](https://img.shields.io/badge/C%2B%2B-20-blue)
![License](https://img.shields.io/badge/license-MIT-green)

<div align="center">

### Open-Source Cross-Platform Peripheral Management Platform

A modern alternative to Logitech G HUB, Razer Synapse, SteelSeries GG and other vendor-locked peripheral management
software.

Linux • Windows • macOS

🚧 Early Development 🚧

</div>

---

## Vision

PeripheralOS aims to provide a unified platform for managing gaming peripherals across operating systems.

Instead of requiring vendor-specific applications for every device, PeripheralOS will offer a single platform capable of
managing:

* Gaming Mice
* Gaming Keyboards
* Gaming Headsets
* Controllers
* RGB Devices
* Generic HID Devices

Our goal is to eliminate vendor lock-in and bring feature parity across Linux, Windows and macOS.

---

## Project Status

PeripheralOS is currently in active alpha development.

Current milestone:

### v0.2.0-alpha

#### Planned

* [ ] Battery Information
* [ ] Firmware Information
* [ ] Device Serial Number
* [ ] Device Capability Discovery

#### Completed

* [x] Device Discovery
* [x] Logitech HID++ Integration
* [x] HID++ Feature Discovery
* [x] Logitech PRO 2 LIGHTSPEED Detection
* [x] Logitech HID++ Device Name Reading

Target device:

* Logitech PRO 2 LIGHTSPEED

Development platform:

* CachyOS Linux

---

## Planned Features

### Device Management

* Device Discovery
* Device Monitoring
* Battery Monitoring
* Firmware Information
* Device Information

### Performance

* DPI Management
* Polling Rate Management
* Lift-Off Distance Configuration
* Sensor Configuration

### RGB

* RGB Effects
* RGB Profiles
* Device Synchronization
* Global Lighting Control

### Profiles

* Device Profiles
* Per-Application Profiles
* Per-Game Profiles
* Automatic Profile Switching

### Macros

* Macro Recording
* Macro Playback
* Multi-Step Macros
* Key Remapping

### Automation

* Application Detection
* Game Detection
* Profile Triggers
* Device Events

### Cloud

* Profile Backup
* Settings Synchronization
* Device Configuration Export

### Extensibility

* Plugin SDK
* Community Device Database
* Third-Party Integrations

---

## Supported Platforms

| Platform | Build Status | Runtime Status       |
|----------|--------------|----------------------|
| Linux    | ✅ Supported  | 🚧 Alpha HID backend |
| Windows  | ✅ Supported  | 📋 Backend planned   |
| macOS    | ✅ Supported  | 📋 Backend planned   |

---

## Planned Device Support

### Logitech

* G PRO Series
* PRO X Series
* LIGHTSPEED Devices
* HID++ Devices

### Future Vendors

* Wraith
* SteelSeries
* Razer
* Corsair
* HyperX
* ASUS ROG
* Generic HID Devices

---

## Architecture

```text
PeripheralOS
│
├── CLI
├── Daemon
├── UI
│
├── Core
├── Device Manager
├── Profile Engine
├── Macro Engine
├── RGB Engine
│
├── Linux Backend
├── Windows Backend
└── macOS Backend
```

### Platform Backends

Linux

* hidraw
* libudev
* DBus

Windows

* SetupAPI
* RawInput
* HID

macOS

* IOKit
* CoreFoundation

---

## Technology Stack

| Component       | Technology     |
|-----------------|----------------|
| Language        | C++20          |
| Build System    | CMake          |
| Build Generator | Ninja          |
| UI              | Qt 6 (Planned) |
| Logging         | spdlog         |
| Formatting      | fmt            |
| JSON            | nlohmann/json  |
| Testing         | doctest        |
| CI/CD           | GitHub Actions |

---

## Building

### Linux

Arch Linux / CachyOS

```bash
sudo pacman -S base-devel cmake ninja git pkgconf systemd
```

Ubuntu / Debian

```bash
sudo apt install build-essential cmake ninja-build git pkg-config libudev-dev
```

Build

```bash
cmake -B build -G Ninja
cmake --build build
```

---

### Windows

Requirements

* Visual Studio 2022
* CMake
* Ninja

Build

```powershell
cmake -B build -G Ninja
cmake --build build
```

---

### macOS

Requirements

* Xcode Command Line Tools
* Homebrew
* CMake
* Ninja

```bash
xcode-select --install
brew install cmake ninja
```

Build

```bash
cmake -B build -G Ninja
cmake --build build
```

---

## Roadmap

### Phase 1 — HID Foundation

* [x] Linux HID Discovery
* [x] Device Identification
* [x] Logitech HID++ Communication
* [x] Feature Discovery
* [x] Device Name Reading

### Phase 2 — Device Telemetry

* [ ] Battery Information
* [ ] Firmware Information
* [ ] Device Information
* [ ] Polling Rate Reading

### Phase 3 — Device Control

* [ ] DPI Reading
* [ ] DPI Configuration
* [ ] Polling Rate Configuration
* [ ] RGB Management

### Phase 4 — Profiles & Automation

* [ ] Profile System
* [ ] Per-Game Profiles
* [ ] Automatic Profile Switching
* [ ] Macro Engine

### Phase 5 — User Interface

* [ ] Qt Device Dashboard
* [ ] RGB Editor
* [ ] Profile Editor

### Phase 6 — Ecosystem

* [ ] Plugin SDK
* [ ] Community Device Database
* [ ] Cloud Synchronization

---

## Contributing

Contributions are welcome.

Please read:

* CONTRIBUTING.md
* SECURITY.md

before opening issues or pull requests.

---

## License

Distributed under the MIT License.

See LICENSE for more information.

---

## Author

Yarkın Gülaçtı

GitHub: https://github.com/yarkingulacti

---

> PeripheralOS is not affiliated with Logitech, Razer, SteelSeries, Corsair, HyperX, ASUS or any other hardware
> manufacturer.
