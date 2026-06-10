# Changelog

All notable changes to this project will be documented in this file.

The format is based on Keep a Changelog and this project follows Semantic Versioning.

---

## [Unreleased]

### Planned

* Battery information
* Firmware information
* DPI reading
* DPI configuration
* Polling rate reading
* Polling rate configuration
* RGB control
* Device profiles
* Macro system
* Per-game profiles
* Qt user interface

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
