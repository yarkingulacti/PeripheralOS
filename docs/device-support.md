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
* Separate UNIFIED_BATTERY capability and live status parsing
* BatteryInfo API

Known limitations:

* Battery percentage is verified in one device state from live `fn=0x10`
* Discharging status is verified for `charging_status=0x00`
* Charging status is verified for `charging_status=0x01`
* Slow charging and full status mappings are implemented but require hardware validation
* Conflicting or unrecognized status values remain unknown

Observed live status output:

```text
UNIFIED_BATTERY feature index: 7
Battery: 58% (Discharging)
Battery: 63% (Charging)
```

---

# LIGHTSPEED Receiver Probe

Temporary receiver support was enabled for `046d:c543`.

Observed interfaces:

```text
/dev/hidraw3 -> UNIFIED_BATTERY discovery failed
/dev/hidraw4 -> UNIFIED_BATTERY discovery failed
/dev/hidraw5 -> UNIFIED_BATTERY feature index: 7
```

Observed result from `/dev/hidraw5`:

```text
HID++ device name: PRO 2 LIGHTSPEED
UNIFIED_BATTERY capability response: 11 01 07 01 0F 0F 01 00 00 00 00 00 00 00 00 00 00 00 00 00
```

Conclusion:

```text
One LIGHTSPEED receiver hidraw interface can proxy HID++ requests for the paired PRO 2 LIGHTSPEED device.
Receiver access returns the same UNIFIED_BATTERY capability response as the direct device interface.
Receiver access does not resolve charging, discharging, or full battery state mapping.
```

---

# Notes

Support levels may change between releases.

Experimental support should not be considered production-ready.
