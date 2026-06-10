# HID++ Notes

This document tracks Logitech HID++ research and implementation notes used by PeripheralOS.

---

# Overview

PeripheralOS currently targets Logitech HID++ 2.0 devices.

The primary development device is:

```text
Logitech PRO 2 LIGHTSPEED
```

---

# HID++ Architecture

Communication flow:

```text
PeripheralOS
    │
    ▼
HID++ Transport
    │
    ▼
Feature Discovery
    │
    ▼
Feature Access
```

---

# Feature Discovery

Feature discovery is performed through the HID++ root feature.

Responsibilities:

* Enumerate supported features
* Resolve feature indexes
* Build capability map

Examples:

```text
DEVICE_NAME
UNIFIED_BATTERY
DEVICE_FW_VERSION
```

---

# DEVICE_NAME

Status:

```text
Implemented
```

Purpose:

Retrieve human-readable device names.

Example:

```text
Logitech PRO 2 LIGHTSPEED
```

---

# UNIFIED_BATTERY

Status:

```text
Planned (v0.2.0-alpha)
```

Purpose:

Retrieve:

* Battery percentage
* Charging state
* Battery status

Potential outputs:

```text
85%
Charging
Discharging
Full
Low
Critical
```

---

# DEVICE_FW_VERSION

Status:

```text
Planned (v0.2.0-alpha)
```

Purpose:

Retrieve firmware version information.

Examples:

```text
Firmware Version
Bootloader Version
Hardware Version
```

---

# SERIAL_NUMBER

Status:

```text
Planned (v0.2.0-alpha)
```

Purpose:

Retrieve unique device identifier when available.

---

# Capability Discovery

Status:

```text
Planned (v0.2.0-alpha)
```

Purpose:

Build a device capability map.

Examples:

```text
Battery
Firmware
RGB
DPI
Polling Rate
Profiles
```

---

# Development Rules

When implementing new HID++ features:

1. Discover feature index first.
2. Implement read-only support before write support.
3. Validate packet sizes.
4. Handle HID++ error responses.
5. Document findings.
6. Avoid device-modifying commands until behavior is understood.

---

# Future HID++ Features

Planned investigations:

* DPI
* Polling Rate
* RGB
* Profiles
* Onboard Memory
* Device Settings

---

# Documentation Rule

Whenever a new HID++ feature is implemented:

Update this document.
