# Changelog

All notable changes to PeripheralOS will be documented in this file.

The format is based on Keep a Changelog and Semantic Versioning.

---

## [Unreleased]

---

## [0.2.0-alpha] - 2026-06-11

### Added

#### Logitech HID++

- Added HID++ UNIFIED_BATTERY feature discovery and full implementation.
- Added BatteryInfo API for battery percentage and status retrieval.
- Added separate UNIFIED_BATTERY capability, live status, and notification parsing.
- Added unified battery status model foundation with charging state detection.
- Added battery feature enumeration support for feature discovery.
- Added hardware-validated discharging detection for UNIFIED_BATTERY `charging_status=0x00`.
- Added hardware-validated charging detection for `charging_status=0x01`.
- Added reference-backed slow charging detection for `charging_status=0x02`.
- Added reference-backed full battery detection for `charging_status=0x03`.
- Added unified battery charging state mapping and field exposure.
- Added UnifiedBatteryReader implementation with robust packet parsing and validation.

#### Development Infrastructure

- Added GitHub issue templates for bug reports, feature requests, device support, and documentation.
- Added GitHub pull request template with standardized review workflow.
- Added VS Code launch configurations for multi-platform debugging support.
- Added VS Code task configurations for build, test, and package workflows.
- Added comprehensive AGENTS.md with 44 sections defining project standards and guidelines.
- Added GitHub Actions and repository automation support.

#### Documentation

- Added Design Principles documentation with project philosophies.
- Added Project Structure documentation describing repository layout.
- Added Development Workflow documentation for contributor guidance.
- Added comprehensive Architecture documentation with layering rules and cross-platform design principles.
- Added detailed Device Support documentation with feature matrices.
- Added expanded HID++ development notes with battery implementation details and probe results.
- Updated Security Policy with comprehensive guidelines.
- Updated Code of Conduct with community standards.
- Added documentation index and repository management guidelines.

#### Project Guidelines and Standards

- Added comprehensive AGENTS.md covering:
    - Output language rules and project identity
    - Agent role and responsibilities
    - Non-negotiable implementation rules (44 mandatory sections)
    - Repository structure guidelines and platform isolation
    - Architecture principles and layering rules
    - Device abstraction patterns and vendor-neutral design
    - HID++ development workflow and feature discovery process
    - Raw packet documentation standards
    - Reverse engineering and protocol safety rules
    - Parser safety and error handling requirements
    - Hardware safety and validation requirements
    - Debug output and runtime verification rules
    - Hardware validation workflow and checklists
    - GitHub workflow and issue lifecycle management
    - Definition of done checklist for all tasks
    - Documentation requirements and templates
    - CHANGELOG and commit conventions
    - Code style and naming conventions
    - Error handling and CMake rules
    - CLI output formatting standards
    - Testing expectations
    - v0.2.0-alpha specific guidance
    - Documentation templates and examples
    - Final engineering principles

#### Project Planning

- Added detailed project roadmap with milestone planning.
- Defined v0.2.0-alpha goals (Battery Support, Firmware Information, Serial Number Support, Capability Discovery).
- Established comprehensive documentation standards.
- Established development standards and best practices.
- Established Conventional Commits formatting for commit messages.

### Changed

- Battery percentage is now accepted exclusively from the UNIFIED_BATTERY live status function.
- Raw HID++ battery fields are retained internally instead of being exposed through BatteryInfo API.
- Battery field naming improved for clarity and consistency in feature enumeration.
- Enhanced HID++ transport matching by exact feature, function, and software ID.

### Fixed

- Fixed invalid interpretation of UNIFIED_BATTERY capability bytes as battery percentage and status.
- Fixed issue where HID++ notifications were incorrectly accepted as request responses.
- Fixed invalid unified battery status mappings that relied on unvalidated assumptions.
- Removed dangerous status interpretations from non-validated protocol fields.

### Tests

- Added focused UNIFIED_BATTERY parser validation tests.
- Added comprehensive unit tests for UnifiedBatteryReader with multiple response scenarios.
- Added tests for malformed packet rejection.
- Added tests for HID++ error packet detection.

### Known Limitations

- Slow charging state mapping (`charging_status=0x02`) requires hardware validation on Logitech PRO 2 LIGHTSPEED.
- Full battery state mapping (`charging_status=0x03`) requires hardware validation on Logitech PRO 2 LIGHTSPEED.
- Conflicting `charging_status=0x04` and unrecognized values remain unknown.
- Battery status requires hardware validation for complete certification.

### Supported Devices

#### Logitech

- PRO 2 LIGHTSPEED (v0.2.0-alpha - Battery Supported)
- LIGHTSPEED Receiver (Detection Only)
- PRO X Wireless Gaming Headset (Detection Only)

#### Wraith

- W75 (Detection Only)

### Notes

This release delivers the first functional battery support for Logitech HID++ devices with comprehensive documentation standards and development infrastructure. The implementation prioritizes hardware safety and proper protocol understanding over feature speed. All battery status interpretations are backed by either hardware validation or reference documentation.

---

## [0.1.0-alpha] - 2026-06-10

### Added

#### Core Infrastructure

- Initial PeripheralOS repository structure
- Cross-platform CMake configuration
- Ninja build support
- GitHub Actions release pipeline
- Automated release artifact generation

#### Linux Backend

- Linux HID discovery
- Linux hidraw enumeration
- Linux device metadata collection

#### Logitech HID++

- Logitech HID++ 2.0 transport implementation
- HID++ feature discovery
- DEVICE_NAME feature support
- Logitech PRO 2 LIGHTSPEED detection
- Device name retrieval

#### Documentation

- Initial README
- Architecture documentation
- Roadmap documentation

### Supported Devices

#### Logitech

- PRO 2 LIGHTSPEED (Experimental)
- LIGHTSPEED Receiver (Detection Only)
- PRO X Wireless Gaming Headset (Detection Only)

#### Wraith

- W75 (Detection Only)

### Known Limitations

#### Device Features

- Battery information unavailable
- Firmware information unavailable
- Serial number unavailable
- DPI support unavailable
- Polling rate support unavailable
- RGB support unavailable

#### Platforms

- Linux backend only
- Windows backend planned
- macOS backend planned

### Notes

This release represents the first functional PeripheralOS prototype capable of discovering Logitech HID++ devices and
retrieving device metadata.

### Next Milestone

#### v0.2.0-alpha

- Battery support
- Firmware information
- Serial number support
- Capability discovery
