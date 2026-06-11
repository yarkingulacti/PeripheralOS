# Architecture

This document describes the high-level architecture of PeripheralOS.

The goal is to provide a maintainable, cross-platform and vendor-independent peripheral management platform.

---

# Architectural Overview

```text
CLI / Future UI
        │
        ▼
Device Manager
        │
        ▼
Capability System
        │
        ▼
Device Layer
        │
        ▼
Vendor Layer
        │
        ▼
Transport Layer
        │
        ▼
Platform Layer
```

---

# Core Layer

Responsibilities:

* Device management
* Runtime services
* Logging
* Configuration
* Capability discovery

Examples:

```text
DeviceManager
CapabilityRegistry
ConfigurationService
Logger
```

Rules:

* Must remain platform-independent.
* Must remain vendor-independent.

---

# Device Layer

Responsibilities:

* Device abstraction
* Unified device model
* Device metadata

Examples:

```text
PeripheralDevice
BatteryInfo
FirmwareInfo
DeviceCapability
```

Rules:

* Exposes unified APIs.
* Must not expose protocol details.

---

# Capability Layer

PeripheralOS uses a capability-based design.

Examples:

```text
Battery
Firmware
DPI
PollingRate
RGB
Profiles
Macros
```

Applications should query capabilities instead of assuming support.

---

# Vendor Layer

Responsibilities:

* Vendor-specific protocols
* Feature discovery
* Device-specific behavior

Examples:

```text
Logitech HID++
Razer Protocols
SteelSeries Protocols
```

Rules:

* Must remain isolated.
* Must not leak vendor-specific details into higher layers.

---

# Transport Layer

Responsibilities:

* Packet transport
* Read/write operations
* Error handling
* Timeouts

Examples:

```text
HID Transport
USB Transport
Future Bluetooth Transport
```

Rules:

* Vendor-independent.
* Platform-independent where possible.

---

# Platform Layer

Responsibilities:

* Native device access
* Enumeration
* Operating system integration

Examples:

```text
Linux hidraw
Windows HID
macOS IOKit
```

Rules:

* Completely isolated from business logic.

---

# Future UI Layer

Planned for v0.6.0-alpha.

Responsibilities:

* Device dashboard
* RGB editor
* Profile management
* Settings management

Technology:

```text
Qt 6
```

---

# Design Goals

PeripheralOS prioritizes:

* Cross-platform design
* Maintainability
* Vendor independence
* Hardware safety
* Documentation quality

All future architectural decisions should align with these goals.
