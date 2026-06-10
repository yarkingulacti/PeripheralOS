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

## UNIFIED_BATTERY (0x1004)

Validation Device:

* Logitech PRO 2 LIGHTSPEED
* VID: 046d
* PID: 40a8

Feature Discovery:

* Feature ID: 0x1004
* Feature Index: 0x07

Current Findings:

* Battery percentage retrieval verified.
* BatteryInfo API implemented.
* Runtime output reports battery percentage correctly.

Unknown Fields:

* Status byte mapping not yet verified.
* Charging state not yet verified.
* Discharging state not yet verified.
* Full battery indication not yet verified.

Validation Level:

* Battery Percentage: Verified
* Battery Status: Experimental

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

---

# Known Working Results

Observed Device:

```text
Logitech PRO 2 LIGHTSPEED
VID: 046d
PID: 40a8
```

Feature Discovery:

```text
DEVICE_NAME       -> 3
UNIFIED_BATTERY   -> 7
```

Observed Battery Response:

```text
11 01 07 01 0F 0F 01 00 00 00 00 00 00 00 00 00 00 00 00 00
```

Current Interpretation:

```text
response[4] = battery percentage
response[5] = secondary battery field
response[6] = status byte
```

Observed BatteryInfo:

```text
BatteryInfo API Output:

Battery: 15%, status=unknown
```

Notes:

* `statusByte=1` observed while charging.
* `statusByte=1` observed while discharging.
* Charging state mapping is unresolved.
* Battery status mapping is unresolved.
