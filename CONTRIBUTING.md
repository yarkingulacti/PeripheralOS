# Contributing to PeripheralOS

Thank you for your interest in contributing to PeripheralOS.

PeripheralOS aims to become a cross-platform peripheral management platform supporting gaming mice, keyboards, headsets, controllers and other HID devices on Linux, Windows and macOS.

---

# Development Philosophy

We prioritize:

* Clean architecture
* Cross-platform compatibility
* Modern C++20
* RAII
* Testability
* Performance
* Long-term maintainability

Contributors should avoid platform-specific implementations unless they are isolated behind platform abstraction layers.

---

# Supported Platforms

| Platform | Status                       |
| -------- | ---------------------------- |
| Linux    | Primary Development Platform |
| Windows  | Supported                    |
| macOS    | Supported                    |

All new features should be designed with cross-platform support in mind.

---

# Development Requirements

## Common Requirements

* CMake >= 3.25
* C++20
* Git
* Ninja

Recommended:

* CLion
* VS Code
* Qt Creator

---

# Linux Development

## Supported Distributions

* Arch Linux
* CachyOS
* Fedora
* Ubuntu
* Debian

## Install Dependencies

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

# Windows Development

## Requirements

* Visual Studio 2022
* MSVC Toolchain
* CMake
* Ninja

Build

```powershell
cmake -B build -G Ninja
cmake --build build
```

Future platform integrations:

* SetupAPI
* HIDAPI
* RawInput

---

# macOS Development

## Requirements

* Xcode Command Line Tools
* CMake
* Ninja

Install tools

```bash
xcode-select --install
brew install cmake ninja
```

Build

```bash
cmake -B build -G Ninja
cmake --build build
```

Future platform integrations:

* IOKit
* CoreFoundation

---

# Repository Structure

```text
PeripheralOS/
├── docs/
├── include/
├── src/
│   ├── core/
│   ├── devices/
│   ├── hid/
│   ├── platform/
│   ├── profiles/
│   └── rgb/
├── tests/
└── third_party/
```

---

# Coding Standards

## C++

Use:

* std::unique_ptr
* std::shared_ptr only when ownership is shared
* std::optional
* std::span
* std::string_view
* enum class

Avoid:

* Raw owning pointers
* Global mutable state
* Platform-specific code outside platform layer
* Macros when constexpr is sufficient

---

# Naming Conventions

Classes

```cpp
class DeviceManager;
class HidDevice;
```

Methods

```cpp
void initialize();
void discoverDevices();
```

Variables

```cpp
std::string deviceName;
int pollingRate;
```

Constants

```cpp
constexpr int DefaultPollingRate = 1000;
```

---

# Platform Abstraction Rules

Platform-specific code must stay inside:

```text
src/platform/
```

Examples:

Linux

```text
src/platform/linux/
```

Windows

```text
src/platform/windows/
```

macOS

```text
src/platform/macos/
```

Business logic must never directly call platform APIs.

---

# Commit Convention

Examples:

```text
feat(hid): add Logitech HID++ discovery

feat(rgb): add RGB profile loader

fix(linux): prevent hidraw descriptor leak

refactor(core): simplify device manager

docs(readme): update build instructions
```

---

# Pull Requests

Before opening a pull request:

* Build successfully
* Run tests
* Follow coding standards
* Update documentation if required

Pull requests should focus on a single feature or fix.

---

# Feature Requests

Feature requests should include:

* Device model
* Platform
* Expected behavior
* Current behavior
* Relevant logs

---

# Bug Reports

Bug reports should include:

* Operating system
* Peripheral model
* Peripheral firmware version
* PeripheralOS version
* Reproduction steps

---

# Long-Term Goals

PeripheralOS aims to support:

* Logitech
* Wraith
* SteelSeries
* Razer
* Corsair
* HyperX
* ASUS ROG
* Generic HID Devices

Features:

* DPI Management
* RGB Management
* Polling Rate Control
* Macro Engine
* Profile System
* Per-Game Profiles
* Cloud Sync
* Plugin SDK

Thank you for contributing to PeripheralOS.
