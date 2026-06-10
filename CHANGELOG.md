# Changelog

All notable changes to this project will be documented in this file.

The format is based on Keep a Changelog and this project follows Semantic Versioning.

---

## [0.1.0-alpha] - 2026-06-10

### Added

* Initial project structure
* Cross-platform CMake configuration
* Linux HID discovery layer
* Linux hidraw device enumeration
* Device identification system
* Logitech device registry
* Logitech HID++ 2.0 transport layer
* HID++ feature discovery support
* HID++ DEVICE_NAME feature support
* Logitech PRO 2 LIGHTSPEED detection
* Logitech PRO 2 LIGHTSPEED device name reading

### Supported Devices

* Logitech PRO 2 LIGHTSPEED (experimental)
* Logitech LIGHTSPEED Receiver
* Logitech PRO X Wireless Gaming Headset
* Wraith W75

### Notes

This release represents the first working proof-of-concept of PeripheralOS.

PeripheralOS can currently:

* Discover HID devices on Linux
* Detect supported Logitech devices
* Open HID devices through hidraw
* Communicate using Logitech HID++ 2.0
* Query device features
* Read Logitech device names

---

## [Unreleased]

### Planned

* Battery information
* DPI reading
* DPI configuration
* Polling rate reading
* Polling rate configuration
* RGB control
* Device profiles
* Macro system
* Per-game profiles
* Qt user interface
