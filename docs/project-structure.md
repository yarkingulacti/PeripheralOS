# Project Structure

This document describes the repository structure used by PeripheralOS.

The goal is to keep the codebase maintainable, scalable and contributor-friendly.

---

# Repository Layout

```text
PeripheralOS
│
├── .github/
├── docs/
├── include/
├── src/
├── tests/
│
├── CHANGELOG.md
├── CONTRIBUTING.md
├── LICENSE
├── README.md
├── SECURITY.md
│
├── CMakeLists.txt
└── ...
```

---

# .github/

Contains GitHub-specific configuration.

Examples:

```text
.github/
├── workflows/
├── ISSUE_TEMPLATE/
└── PULL_REQUEST_TEMPLATE.md
```

Responsibilities:

* CI/CD workflows
* Release automation
* Issue templates
* Pull request templates

---

# docs/

Project documentation.

Examples:

```text
docs/
├── architecture.md
├── design-principles.md
├── device-support.md
├── hidpp-notes.md
├── roadmap.md
├── development-workflow.md
└── project-structure.md
```

Responsibilities:

* Architecture documentation
* Reverse engineering notes
* Roadmaps
* Development guidelines

Documentation is considered part of the implementation.

---

# include/

Public headers.

Example:

```text
include/
├── peripheralos/
│   ├── device/
│   ├── hid/
│   ├── vendor/
│   └── core/
```

Responsibilities:

* Public interfaces
* Shared declarations
* API contracts

Implementation details should remain inside src/.

---

# src/

Application source code.

Example future structure:

```text
src/
├── core/
├── device/
├── hid/
├── vendor/
│   └── logitech/
├── platform/
│   ├── linux/
│   ├── windows/
│   └── macos/
└── cli/
```

---

# src/core/

Platform-independent business logic.

Examples:

* DeviceManager
* Capability system
* Configuration
* Logging
* Runtime services

Must not directly access operating system APIs.

---

# src/device/

Device abstraction layer.

Examples:

* PeripheralDevice
* BatteryInfo
* FirmwareInfo
* DeviceCapability

Responsibilities:

* Unified device model
* Device metadata
* Capability exposure

---

# src/hid/

Generic HID transport layer.

Responsibilities:

* Packet transport
* Read/write operations
* HID abstractions
* Timeouts
* Error handling

Should remain vendor-independent.

---

# src/vendor/

Vendor-specific implementations.

Example:

```text
src/vendor/
├── logitech/
├── razer/
├── steelseries/
└── wraith/
```

Responsibilities:

* Vendor protocols
* Feature implementations
* Device-specific behavior

---

# src/platform/

Operating system backends.

Example:

```text
src/platform/
├── linux/
├── windows/
└── macos/
```

Responsibilities:

* Device enumeration
* Native HID access
* Platform integration

Platform code must remain isolated.

---

# src/cli/

Command-line interface.

Examples:

```bash
peripheralos devices
peripheralos battery
peripheralos device info
```

Responsibilities:

* User interaction
* Command parsing
* Output formatting

---

# tests/

Automated tests.

Example:

```text
tests/
├── unit/
├── integration/
└── fixtures/
```

Responsibilities:

* Unit testing
* Integration testing
* Regression testing

---

# Design Rules

* Core code must remain platform-independent.
* Vendor logic must remain isolated.
* Platform-specific code must remain isolated.
* Documentation must be updated when functionality changes.
* New features should be accompanied by tests whenever practical.
