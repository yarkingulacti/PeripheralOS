# PeripheralOS

![CI](https://github.com/yarkingulacti/PeripheralOS/actions/workflows/release.yml/badge.svg)
![Release](https://img.shields.io/github/v/release/yarkingulacti/PeripheralOS)
![License](https://img.shields.io/github/license/yarkingulacti/PeripheralOS)
![Issues](https://img.shields.io/github/issues/yarkingulacti/PeripheralOS)
![Pull Requests](https://img.shields.io/github/issues-pr/yarkingulacti/PeripheralOS)
![Last Commit](https://img.shields.io/github/last-commit/yarkingulacti/PeripheralOS)
![Repo Size](https://img.shields.io/github/repo-size/yarkingulacti/PeripheralOS)
![Stars](https://img.shields.io/github/stars/yarkingulacti/PeripheralOS)
![Forks](https://img.shields.io/github/forks/yarkingulacti/PeripheralOS)

![Milestone](https://img.shields.io/badge/milestone-v0.2.0--alpha-purple)
![Status](https://img.shields.io/badge/status-early%20development-orange)

![Linux](https://img.shields.io/badge/Linux-Alpha-success)
![Windows](https://img.shields.io/badge/Windows-Planned-lightgrey)
![macOS](https://img.shields.io/badge/macOS-Planned-lightgrey)

![C++](https://img.shields.io/badge/C%2B%2B-20-blue)
![CMake](https://img.shields.io/badge/CMake-3.25%2B-064F8C)
![Ninja](https://img.shields.io/badge/Ninja-Build-44CC11)

![Qt](https://img.shields.io/badge/Qt%206-Planned-41CD52)
![Logitech HID++](https://img.shields.io/badge/Logitech-HID++%202.0-00B8FC)
![Open Source](https://img.shields.io/badge/Open%20Source-Yes-success)
![Contributions](https://img.shields.io/badge/Contributions-Welcome-brightgreen)
![Documentation](https://img.shields.io/badge/Docs-Available-blue)

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

Instead of requiring vendor-specific applications for every device, PeripheralOS provides a single platform capable of
managing:

* Gaming Mice
* Gaming Keyboards
* Gaming Headsets
* Controllers
* RGB Devices
* Generic HID Devices

Our goal is to eliminate vendor lock-in and bring feature parity across Linux, Windows and macOS.

---

## Why PeripheralOS?

Gaming peripherals are increasingly locked behind vendor-specific ecosystems.

A user may need to install multiple applications just to manage devices from different manufacturers:

* Logitech G HUB
* Razer Synapse
* SteelSeries GG
* Corsair iCUE
* Armoury Crate

PeripheralOS aims to provide a single open-source platform that works across operating systems and vendors.

### Core Principles

* Cross-platform support
* Local-first operation
* No vendor lock-in
* Open documentation
* Community-driven device support
* Long-term maintainability

---

## Project Status

PeripheralOS is currently in active alpha development.

### Current Milestone

#### v0.2.0-alpha

##### Planned

* [ ] #4 Firmware Information Reading
* [ ] #5 Device Serial Number Support
* [ ] #6 Device Capability Discovery
* [ ] #3 Battery Charging/Full Hardware Validation

##### Completed

* [x] Device Discovery
* [x] Linux HID Enumeration
* [x] Logitech HID++ Integration
* [x] HID++ Feature Discovery
* [x] Logitech PRO 2 LIGHTSPEED Detection
* [x] Logitech HID++ Device Name Reading
* [x] Logitech HID++ UNIFIED_BATTERY Discovery
* [x] Battery Percentage Reading
* [x] BatteryInfo API Exposure
* [x] HID++ Unified Battery Status Mapping

### Current Target Device

* Logitech PRO 2 LIGHTSPEED

### Primary Development Platform

* Linux (CachyOS)

---

## Current Device Support

| Vendor   | Device                        | Support Level  |
|----------|-------------------------------|----------------|
| Logitech | PRO 2 LIGHTSPEED              | Experimental   |
| Logitech | LIGHTSPEED Receiver           | Detection Only |
| Logitech | PRO X Wireless Gaming Headset | Detection Only |
| Wraith   | W75                           | Detection Only |

For detailed information see:

* docs/device-support.md

---

## Supported Platforms

| Platform | Build Support | Runtime Support |
|----------|---------------|-----------------|
| Linux    | ✅             | 🚧 Alpha        |
| Windows  | ✅             | 📋 Planned      |
| macOS    | ✅             | 📋 Planned      |

---

## Technology Stack

| Component    | Technology     |
|--------------|----------------|
| Language     | C++20          |
| Build System | CMake          |
| Generator    | Ninja          |
| UI           | Qt 6 (Planned) |
| Logging      | spdlog         |
| Formatting   | fmt            |
| JSON         | nlohmann/json  |
| Testing      | doctest        |
| CI/CD        | GitHub Actions |

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

### Windows

Requirements:

* Visual Studio 2022
* CMake
* Ninja

Build:

```powershell
cmake -B build -G Ninja
cmake --build build
```

### macOS

Requirements:

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

## Documentation

### Core Documentation

* docs/design-principles.md
* docs/architecture.md
* docs/project-structure.md
* docs/development-workflow.md

### Development Documentation

* docs/device-support.md
* docs/hidpp-notes.md
* docs/roadmap.md

### Community Documentation

* CONTRIBUTING.md
* SECURITY.md
* CODE_OF_CONDUCT.md
* CHANGELOG.md

---

## Roadmap

### v0.2.0-alpha

* Battery Percentage Support
* Battery Charging State Detection
* Battery Status Mapping
* Firmware Information
* Serial Number Support
* Capability Discovery

### v0.3.0-alpha

* DPI Support
* Polling Rate Support

### v0.4.0-alpha

* RGB Support
* Profile System

### v0.5.0-alpha

* Daemon
* Automation
* Device Monitoring

### v0.6.0-alpha

* Qt User Interface

### v1.0.0

* Stable Linux Release
* Complete Logitech Workflow

---

## Contributing

Contributions are welcome.

Please review:

* CONTRIBUTING.md
* SECURITY.md
* CODE_OF_CONDUCT.md

before opening issues or pull requests.

---

## License

Distributed under the MIT License.

See LICENSE for details.

---

## Maintainer

Yarkın Gülaçtı

GitHub: https://github.com/yarkingulacti

---

> PeripheralOS is not affiliated with Logitech, Razer, SteelSeries, Corsair, HyperX, ASUS, Wraith or any other hardware
> manufacturer.
