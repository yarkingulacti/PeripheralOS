# Design Principles

This document defines the engineering principles that guide the design and development of PeripheralOS.

All architectural decisions, implementations and future features should align with these principles.

---

# 1. Cross-Platform First

PeripheralOS is designed as a cross-platform application from day one.

Supported platforms:

* Linux
* Windows
* macOS

Platform-specific implementations must remain isolated behind abstraction layers.

Core business logic must remain platform-independent.

---

# 2. Device Abstraction

PeripheralOS manages peripherals, not vendor protocols.

Users should interact with concepts such as:

* Battery
* DPI
* Polling Rate
* RGB
* Profiles
* Firmware Information

Protocol details should remain implementation details.

---

# 3. Read-Only Before Write

Device safety has priority over feature velocity.

Before implementing writable functionality:

1. Discover protocol behavior
2. Implement read-only support
3. Validate responses
4. Document findings
5. Implement write support

---

# 4. Hardware Safety

PeripheralOS must never intentionally place user hardware at risk.

Avoid:

* Unknown firmware commands
* Unsafe memory writes
* Experimental device resets
* Destructive protocol operations

When behavior is uncertain:

> Do not send the command.

---

# 5. Vendor Independence

PeripheralOS exists to reduce vendor lock-in.

The project should not depend on:

* Logitech G HUB
* Razer Synapse
* SteelSeries GG
* Vendor cloud services

Whenever possible, functionality should work locally.

---

# 6. Documentation as Code

Documentation is part of the implementation.

A feature is not complete until documentation is updated.

Relevant files include:

* README.md
* CHANGELOG.md
* docs/architecture.md
* docs/device-support.md
* docs/hidpp-notes.md
* docs/roadmap.md

---

# 7. Capability-Based Design

Not every device supports every feature.

PeripheralOS should expose capabilities explicitly.

Examples:

* Battery
* RGB
* Polling Rate
* Profiles
* Macros
* Firmware Information

Applications should query capabilities rather than making assumptions.

---

# 8. Open Knowledge

Reverse engineering discoveries should be documented whenever legally permissible.

Knowledge should not remain hidden inside source code.

New protocol discoveries should be recorded in:

* docs/hidpp-notes.md

---

# 9. Maintainability Over Shortcuts

The project favors maintainable architecture over temporary hacks.

Preferred:

* Clear abstractions
* Explicit ownership
* Modular design
* Testability

Avoid:

* Global mutable state
* Hidden dependencies
* Hardcoded device behavior
* Unexplained magic values

---

# 10. Community Friendly Development

PeripheralOS is an open-source project.

Contributors should be able to:

* Understand the architecture
* Build the project easily
* Add device support safely
* Follow documented processes

---

# 11. Privacy First

PeripheralOS should function locally whenever possible.

The project should avoid:

* Mandatory cloud services
* Unnecessary telemetry
* User tracking

Users should retain full control of their devices and data.

---

# 12. Long-Term Vision

PeripheralOS aims to become the open standard for cross-platform peripheral management.

Success means:

* Vendor-independent device management
* Consistent user experience
* Open documentation
* Community-driven device support
* Professional engineering standards
