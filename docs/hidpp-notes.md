# Logitech HID++ Notes

This document contains implementation notes for Logitech HID++ support in PeripheralOS.

It is intended for development and reverse engineering notes.

---

## Disclaimer

PeripheralOS is not affiliated with Logitech.

HID++ support is implemented through public knowledge, observed device behavior, Linux kernel behavior and community
research.

---

## Current Target

Primary test device:

```text
Logitech PRO 2 LIGHTSPEED
VID:PID 046d:40a8
Receiver VID:PID 046d:c543
Protocol: HID++ 4.2 according to Solaar output
````

---

## HID++ Concepts

### Device Index

HID++ packets include a device index.

For devices connected through a receiver:

```text
0x01..0x06 -> paired devices
0xff       -> receiver
```

For the Logitech PRO 2 LIGHTSPEED, `0x01` is currently used.

---

## Report Types

### Short Report

```text
Report ID: 0x10
Size: 7 bytes
```

Used for short HID++ requests.

General shape:

```text
[report_id, device_index, feature_index, function_id | software_id, param0, param1, param2]
```

### Long Report

```text
Report ID: 0x11
Size: usually 20 bytes
```

Used for longer responses and larger payloads.

---

## Software ID

PeripheralOS currently uses:

```text
Software ID: 0x01
```

This is encoded in the low nibble of the function byte.

---

## Feature Discovery

HID++ 2.0 features are discovered through the root feature.

Root feature:

```text
Feature ID: 0x0000
Feature Index: 0x00
```

Example request:

```text
GetFeature(0x0005)
```

Used to discover:

```text
DEVICE_NAME -> 0x0005
```

Current known result:

```text
DEVICE_NAME feature index: 3
```

---

## DEVICE_NAME Feature

Feature ID:

```text
0x0005
```

Current behavior on Logitech PRO 2 LIGHTSPEED:

```text
Name length: 16
Name: PRO 2 LIGHTSPEED
```

Current implementation:

* Discover feature index for `0x0005`
* Request name length
* Request name chunks
* Assemble string

---

## UNIFIED_BATTERY Feature

Feature ID:

```text
0x1004
```

Planned for:

```text
v0.2.0-alpha
```

Expected information:

* Battery percentage
* Battery status
* Charging state

Known Solaar-style output:

```text
UNIFIED BATTERY {1004}
Battery: 31%, BatteryStatus.RECHARGING
```

Implementation tasks:

* Discover feature index
* Send battery status request
* Parse response
* Map status bytes to enum
* Expose through high-level API

---

## DEVICE FW VERSION Feature

Feature ID:

```text
0x0003
```

Planned for:

```text
v0.2.0-alpha
```

Expected information:

* Firmware type
* Firmware version
* Model ID
* Unit ID

---

## Important Implementation Rules

### Read-only First

New HID++ features must first be implemented as read-only.

Do not write device configuration until packet structure is understood.

### Filter Input Reports

HID raw reads may return normal mouse input reports.

The HID++ client must filter responses by:

* Report ID
* Device index
* Feature index
* Error response

### Error Responses

HID++ errors should not be treated as valid feature data.

Observed error indicator:

```text
response[2] == 0xff
```

### Avoid Root Commands That Modify State

Feature discovery and information reading are safe.

Configuration writes must be delayed until later milestones.

---

## Current Known Feature IDs

| Feature                         |       ID | Status      |
|---------------------------------|---------:|-------------|
| ROOT                            | `0x0000` | Used        |
| FEATURE SET                     | `0x0001` | Planned     |
| DEVICE FW VERSION               | `0x0003` | Planned     |
| DEVICE NAME                     | `0x0005` | Implemented |
| UNIFIED BATTERY                 | `0x1004` | Planned     |
| EXTENDED ADJUSTABLE DPI         | `0x2202` | Planned     |
| EXTENDED ADJUSTABLE REPORT RATE | `0x8061` | Planned     |
| RGB EFFECTS                     | `0x8071` | Planned     |
| ONBOARD PROFILES                | `0x8100` | Planned     |

---

## Test Output

Known working output from v0.1.0-alpha:

```text
HID++ DEVICE_NAME feature index: 3
HID++ device name length: 16
HID++ device name: PRO 2 LIGHTSPEED
```

---

## Open Questions

* Exact UNIFIED_BATTERY response format for PRO 2 LIGHTSPEED
* Firmware response chunking behavior
* DPI read/write packet structure
* Polling rate write confirmation
* RGB effect format
* Onboard profile layout
