# Device Support

This document tracks current and planned device support within PeripheralOS.

---

# Support Levels

## Supported

The device is fully supported and tested.

Features:

* Detection
* Telemetry
* Configuration
* Profile Management

---

## Experimental

The device is functional but not all features are implemented or fully validated.

Features may change between releases.

---

## Detection Only

PeripheralOS can detect the device and retrieve basic information.

Advanced functionality is not yet implemented.

---

## Planned

The device is expected to be supported in the future.

No implementation currently exists.

---

## Unsupported

The device is not currently targeted.

---

# Logitech Devices

| Device                        | Support Level  | Notes                      |
|-------------------------------|----------------|----------------------------|
| PRO 2 LIGHTSPEED              | Experimental   | Primary development device |
| LIGHTSPEED Receiver           | Detection Only | Enumeration supported      |
| PRO X Wireless Gaming Headset | Detection Only | Basic identification only  |
| G PRO X Superlight            | Planned        | Future HID++ support       |
| G502 X                        | Planned        | Future HID++ support       |

---

# Wraith Devices

| Device | Support Level  | Notes                  |
|--------|----------------|------------------------|
| W75    | Detection Only | Initial testing target |

---

# Future Vendors

## Planned

* Razer
* SteelSeries
* Corsair
* HyperX
* ASUS ROG

---

# Feature Support Matrix

| Feature               | Status       |
|-----------------------|--------------|
| Device Discovery      | Supported    |
| Device Identification | Supported    |
| Device Name Reading   | Supported    |
| Battery Information   | Experimental |
| Firmware Information  | Planned      |
| Serial Number         | Planned      |
| DPI Support           | Planned      |
| Polling Rate Support  | Planned      |
| RGB Support           | Planned      |
| Profile Support       | Planned      |
| Macro Support         | Planned      |

---

# Logitech PRO 2 LIGHTSPEED

Current capabilities:

* Device detection
* Device identification
* DEVICE_NAME support
* UNIFIED_BATTERY feature discovery
* Battery percentage reading
* BatteryInfo API

Known limitations:

* Charging state detection unavailable
* Battery status mapping unavailable

Observed results:

```text
UNIFIED_BATTERY feature index: 7
Battery: 15%, status=unknown
```

---

# Notes

Support levels may change between releases.

Experimental support should not be considered production-ready.
