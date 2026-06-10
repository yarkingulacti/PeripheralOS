# Changelog

All notable changes to PeripheralOS will be documented in this file.

The format is based on Keep a Changelog and Semantic Versioning.

---

## [Unreleased]

### Added

#### Logitech HID++

* Added HID++ UNIFIED_BATTERY feature discovery.
* Added BatteryInfo API exposure.
* Added separate UNIFIED_BATTERY capability, live status, and notification parsing.
* Added hardware-validated discharging detection for UNIFIED_BATTERY `charging_status=0x00`.
* Added hardware-validated charging detection for `charging_status=0x01`.
* Added reference-backed slow charging detection for `charging_status=0x02`.
* Added reference-backed full detection for `charging_status=0x03`.

### Changed

* Battery percentage is now accepted only from the UNIFIED_BATTERY live status function.
* Raw HID++ battery fields are retained internally instead of exposed through BatteryInfo.

### Fixed

* Stopped interpreting UNIFIED_BATTERY capability bytes as battery percentage and status.
* Matched HID++ replies by exact feature, function, and software ID to avoid accepting notifications as request responses.

### Tests

* Added focused UNIFIED_BATTERY parser validation tests.

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

* Slow charging and full status mappings require hardware validation on Logitech PRO 2 LIGHTSPEED.
* Conflicting `charging_status=0x04` and unrecognized values remain unknown.

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
