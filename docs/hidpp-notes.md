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

* Capability discovery and live status parsing are implemented separately.
* Live status is requested with wire function ID `0x10`.
* BatteryInfo API implemented.
* Raw battery fields are retained internally and are not exposed through BatteryInfo.

Exposed Fields:

* percentage
* status

Unknown Fields:

* `charging_status=0x04` meaning is conflicting across reference implementations.
* Reserved and unrecognized charging status values remain unknown.
* External power status mapping is not exposed.

Validation Level:

* Battery Percentage: Verified in one device state from live `fn=0x10`
* Battery API: Implemented
* Discharging Status: Verified on Logitech PRO 2 LIGHTSPEED
* Charging Status (`0x01`): Verified on Logitech PRO 2 LIGHTSPEED
* Slow Charging (`0x02`) and Full Status (`0x03`): Implemented from established references; hardware validation pending

### UNIFIED_BATTERY Function Probe

Previously recorded read-only function probe on Logitech PRO 2 LIGHTSPEED:

```text
fn=0x00 -> 11 01 07 01 0F 0F 01 00 00 00 00 00 00 00 00 00 00 00 00 00
fn=0x01 -> 11 01 07 11 3A 04 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fn=0x02 -> 11 01 07 21 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
fn=0x03 -> 11 01 FF 07 31 07 00 00 00 00 00 00 00 00 00 00 00 00 00 00
```

Observed interpretation:

```text
fn=0x00 returns capability fields.
fn=0x01 sends wire function ID 0x10 and returns live battery status fields.
fn=0x02 returns zeroed data.
fn=0x03 returns a HID++ error response.
```

Validation status:

```text
fn=0x00 capability parsing implemented; hardware revalidation required.
fn=0x01 live status parsing implemented; hardware revalidation required.
fn=0x02 meaning unresolved.
fn=0x03 unsupported or invalid function.
```

Live status packet fields:

```text
params[0] = state of charge percentage
params[1] = level flags
params[2] = charging status
params[3] = external power status
```

Safety decision:

* Percentage is updated only from a successful live `fn=0x10` response.
* Notifications update internal raw state but do not replace the last live percentage.
* `charging_status=0x00` maps to `Discharging`; this was validated on an unplugged PRO 2 LIGHTSPEED.
* `charging_status=0x01` and `0x02` map to `Charging`.
* `charging_status=0x03` maps to `Full`.
* `charging_status=0x04` and unrecognized values map to `Unknown`.
* Slow charging and full mappings require physical-state validation on PRO 2 LIGHTSPEED.

Reference implementations:

* [Linux `hid-logitech-hidpp` driver](https://github.com/torvalds/linux/blob/master/drivers/hid/hid-logitech-hidpp.c), Unified Battery `0x1004`
* [Solaar Unified Battery decoder](https://github.com/pwr-Solaar/Solaar/blob/master/lib/logitech_receiver/hidpp20.py)
* [Logitech HID++ 2.0 draft (2012)](https://lekensteyn.nl/files/logitech/logitech_hidpp_2.0_specification_draft_2012-06-04.pdf), for HID++ framing conventions

### Live Status Validation Record

```text
Device: Logitech PRO 2 LIGHTSPEED
Vendor: Logitech
Vendor ID: 046d
Product ID: 40a8
Connection: USB HID interface
Platform: Linux
Kernel / OS: Linux 7.0.11-1-cachyos
Feature: UNIFIED_BATTERY (0x1004), feature index 0x07
Function: live status, wire fn=0x10
Observed Packet: 11 01 07 11 3A 04 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Parsed Output: Battery: 58% (Discharging)
Validation Status: Verified for percentage and discharging in the current device state
Notes: Three consecutive reads were consistent and the device was confirmed
       unplugged/discharging. Slow charging and full,
       reconnect, and notification behavior remain unverified. No kernel
       power_supply oracle was available.
```

### Charging Validation Record

```text
Device: Logitech PRO 2 LIGHTSPEED
Vendor: Logitech
Vendor ID: 046d
Product ID: 40a8
Connection: USB HID interface, externally powered
Platform: Linux
Kernel / OS: Linux 7.0.11-1-cachyos
Feature: UNIFIED_BATTERY (0x1004), feature index 0x07
Function: live status, wire fn=0x10
Observed Packet: 11 01 07 11 3F 04 01 01 00 00 00 00 00 00 00 00 00 00 00 00
Parsed Output: Battery: 63% (Charging)
Validation Status: Verified for charging_status=0x01
Notes: Device was actively charging. Raw packet was captured through a debugger;
       no production debug output was added.
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

Previously Observed Capability Response:

```text
11 01 07 01 0F 0F 01 00 00 00 00 00 00 00 00 00 00 00 00 00
```

Current Interpretation:

```text
response[4] = supported level flags
response[5] = capability flags
response[6] = trailing capability response data; meaning unverified
```

Previously Observed CLI Output:

```text
BatteryInfo API Output:

Battery: 15%, status=unknown
```

Notes:

* The previous CLI output incorrectly interpreted capability byte `response[4]` as battery percentage.
* Three consecutive live `fn=0x10` reads contained `charging_status=0x00` while the device was confirmed discharging.
* Multiple-state, notification, and reconnect validation remain outstanding.
* Charging status `0x01` is verified on this device.
* Slow charging `0x02` and full `0x03` are implemented from established references but remain unverified on this device.
* `charging_status=0x04` and external power mappings remain unresolved.

Current BatteryInfo Model:

```text
percentage     -> live fn=0x10 response only
status         -> discharging / charging / full / safe fallback (unknown)
raw fields     -> retained internally
```

Charging state mapping is verified for `charging_status=0x01`.

Slow charging state mapping is implemented for `charging_status=0x02`; hardware validation is pending.

Discharging state mapping is verified for `charging_status=0x00`.

Full battery state mapping is implemented for `charging_status=0x03`; hardware validation is pending.
