# Changelog

All notable changes to this project will be documented in this file.

## [Unreleased]

### Planned

#### Battery Support

* Logitech HID++ UNIFIED_BATTERY feature support
* Battery percentage reading
* Battery status reading
* Charging state detection

#### Device Information

* Firmware information reading
* Serial number reading
* Capability discovery

#### Internal Improvements

* Device abstraction improvements
* HID++ feature wrappers
* Improved runtime diagnostics

---

## [0.1.1-alpha] - 2026-06-10

### 🚀 Added

#### Documentation

- Added `SECURITY.md`
- Added `CODE_OF_CONDUCT.md`
- Added detailed architecture documentation
- Added roadmap documentation
- Added device support documentation
- Added Logitech HID++ development notes
- Added coding standards documentation
- Added release template documentation

#### Project Management

- Added GitHub issue planning for `v0.2.0-alpha`
- Added milestone planning for future alpha releases
- Added label strategy for issue management

### 🔧 Changed

#### Release Process

- Improved release process documentation
- Improved changelog and release notes standards
- Improved contributor guidance
- Improved GitHub Actions compatibility with newer action versions

### 📝 Notes

This release does not introduce new runtime device functionality.

It improves project documentation, contributor onboarding, release process consistency and project planning for future
PeripheralOS development.

### 🎯 Next Milestone

#### v0.2.0-alpha

Planned objectives:

- Battery information support
- Firmware information support
- Device serial number support
- Device capability discovery
- Expanded Logitech HID++ coverage

---

## [0.1.0-alpha] - 2026-06-10

### Added

* Initial project structure
* Cross-platform CMake configuration
* Linux, Windows and macOS Release build configuration
* Release packaging configuration with CPack
* Git commit metadata embedding
* Linux HID discovery layer
* Linux hidraw device enumeration
* Device identification system
* Logitech device registry
* Logitech HID++ 2.0 transport layer
* HID++ feature discovery support
* HID++ DEVICE_NAME feature support
* Logitech PRO 2 LIGHTSPEED detection
* Logitech PRO 2 LIGHTSPEED device name length reading
* Logitech PRO 2 LIGHTSPEED device name reading
* Improved runtime information output
* GitHub Actions release workflow plan

### Supported Devices

* Logitech PRO 2 LIGHTSPEED experimental Linux HID++ support
* Logitech LIGHTSPEED Receiver detection
* Logitech PRO X Wireless Gaming Headset detection
* Wraith W75 detection

### Release Artifacts

This release is intended to provide binaries for:

* Linux x86_64
* Windows x86_64
* macOS arm64 / x86_64 depending on GitHub hosted runner availability

### Notes

This release represents the first working proof-of-concept of PeripheralOS.

PeripheralOS can currently:

* Build on Linux, Windows and macOS
* Discover HID devices on Linux
* Detect supported Logitech devices
* Open HID devices through hidraw
* Communicate using Logitech HID++ 2.0
* Query HID++ device features
* Read Logitech HID++ device names

Windows and macOS binaries are currently build-validation artifacts. Runtime device backends for Windows and macOS are
planned for future versions.
