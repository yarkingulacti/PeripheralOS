# Changelog

All notable changes to PeripheralOS will be documented in this file.

The format is based on Keep a Changelog and Semantic Versioning.

---

## [Unreleased]

### Added

#### Logitech HID++

* Added HID++ UNIFIED_BATTERY feature discovery.
* Added battery percentage reading.
* Added BatteryInfo API exposure.
* Added battery response parsing for Logitech PRO 2 LIGHTSPEED.

#### Documentation

* Added Design Principles documentation
* Added Project Structure documentation
* Added Development Workflow documentation
* Expanded Architecture documentation
* Expanded Device Support documentation
* Expanded HID++ development notes
* Added Security Policy
* Added Code of Conduct

#### Repository Management

* Added documentation index
* Added contributor workflow
* Added project roadmap
* Added release workflow documentation

#### Project Planning

* Defined v0.2.0-alpha goals
* Defined future milestone roadmap
* Established documentation standards
* Established development standards

### Known Limitations

* Charging state detection is unresolved.
* Battery status mapping is unresolved.
* `statusByte=1` was observed both while charging and discharging.

---

## [0.1.0-alpha] - 2026-06-10

### Added

#### Core Infrastructure

* Initial PeripheralOS repository structure
* Cross-platform CMake configuration
* Ninja build support
* GitHub Actions release pipeline
* Automated release artifact generation

#### Linux Backend

* Linux HID discovery
* Linux hidraw enumeration
* Linux device metadata collection

#### Logitech HID++

* Logitech HID++ 2.0 transport implementation
* HID++ feature discovery
* DEVICE_NAME feature support
* Logitech PRO 2 LIGHTSPEED detection
* Device name retrieval

#### Documentation

* Initial README
* Architecture documentation
* Roadmap documentation

### Supported Devices

#### Logitech

* PRO 2 LIGHTSPEED (Experimental)
* LIGHTSPEED Receiver (Detection Only)
* PRO X Wireless Gaming Headset (Detection Only)

#### Wraith

* W75 (Detection Only)

### Known Limitations

#### Device Features

* Battery information unavailable
* Firmware information unavailable
* Serial number unavailable
* DPI support unavailable
* Polling rate support unavailable
* RGB support unavailable

#### Platforms

* Linux backend only
* Windows backend planned
* macOS backend planned

### Notes

This release represents the first functional PeripheralOS prototype capable of discovering Logitech HID++ devices and
retrieving device metadata.

### Next Milestone

#### v0.2.0-alpha

* Battery support
* Firmware information
* Serial number support
* Capability discovery
