# PeripheralOS

<div align="center">

### Open-Source Cross-Platform Peripheral Management Platform

A modern alternative to Logitech G HUB, Razer Synapse, SteelSeries GG and other vendor-locked peripheral management software.

Linux • Windows • macOS

🚧 Early Development 🚧

</div>

---

## Vision

PeripheralOS aims to provide a unified platform for managing gaming peripherals across operating systems.

Instead of requiring vendor-specific applications for every device, PeripheralOS will offer a single platform capable of managing:

* Gaming Mice
* Gaming Keyboards
* Gaming Headsets
* Controllers
* RGB Devices
* Generic HID Devices

Our goal is to eliminate vendor lock-in and bring feature parity across Linux, Windows and macOS.

---

## Project Status

PeripheralOS is currently in early development.

Current milestone:

### v0.1.0

* [ ] Device Discovery
* [ ] Logitech HID++ Integration
* [ ] Battery Information
* [ ] DPI Reading
* [ ] DPI Configuration
* [ ] Polling Rate Reading
* [ ] Polling Rate Configuration

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

| Platform | Status            |
| -------- | ----------------- |
| Linux    | 🚧 In Development |
| Windows  | 📋 Planned        |
| macOS    | 📋 Planned        |

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
| --------------- | -------------- |
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

### Phase 1 — Core Foundation

* Device Discovery
* HID Layer
* Logitech HID++ Support
* Battery Information
* DPI Control

### Phase 2 — Device Features

* Polling Rate Control
* RGB Management
* Profile Management

### Phase 3 — Automation

* Per-Game Profiles
* Application Detection
* Automatic Switching

### Phase 4 — User Experience

* Qt User Interface
* Device Dashboard
* Profile Editor

### Phase 5 — Ecosystem

* Plugin SDK
* Community Integrations
* Cloud Synchronization

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

> PeripheralOS is not affiliated with Logitech, Razer, SteelSeries, Corsair, HyperX, ASUS or any other hardware manufacturer.
