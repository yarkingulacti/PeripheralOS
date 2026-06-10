# Device Support

This document tracks device support status in PeripheralOS.

Support levels are intentionally explicit so users understand what currently works.

---

## Support Levels

### Detection Only

PeripheralOS can detect the device but cannot control it yet.

### Experimental

Some functionality works but APIs or behavior may change.

### Functional

Core features work and are usable for daily testing.

### Stable

The device is considered production-ready.

---

## Current Support Matrix

| Vendor   | Device                        |     VID:PID | Kind         | Support Level  | Notes                            |
|----------|-------------------------------|------------:|--------------|----------------|----------------------------------|
| Logitech | PRO 2 LIGHTSPEED              | `046d:40a8` | Mouse        | Experimental   | HID++ device name reading works  |
| Logitech | LIGHTSPEED Receiver           | `046d:c543` | Receiver     | Detection Only | Receiver is detected             |
| Logitech | PRO X Wireless Gaming Headset | `046d:0aba` | Headset      | Detection Only | Device is detected               |
| Wraith   | W75                           | `2e3c:c365` | Keyboard     | Detection Only | Device is detected               |
| Unknown  | UNIW0001 Touchpad             | `093a:0255` | Input Device | Detection Only | Detected through HID enumeration |

---

## Logitech PRO 2 LIGHTSPEED

### Status

Experimental.

### Current Capabilities

- Device discovery
- Device identification
- Linux hidraw open
- Logitech HID++ 2.0 communication
- HID++ feature discovery
- DEVICE_NAME feature discovery
- Device name length reading
- Device name reading

### Known Working Output

```text
046d:40a8 -> Logitech PRO 2 LIGHTSPEED
HID++ DEVICE_NAME feature index: 3
HID++ device name length: 16
HID++ device name: PRO 2 LIGHTSPEED
````

### Planned Capabilities

* Battery percentage
* Battery status
* Charging state
* Firmware information
* Serial number
* DPI reading
* DPI configuration
* Polling rate reading
* Polling rate configuration
* RGB control
* Onboard profile support

---

## Logitech LIGHTSPEED Receiver

### Status

Detection Only.

### Current Capabilities

* Device discovery
* Device identification

### Notes

The receiver appears as multiple HID interfaces.

The connected mouse may appear as a HID++ child device with a separate product ID.

Example:

```text
046d:c543 -> Logitech LIGHTSPEED Receiver
046d:40a8 -> Logitech PRO 2 MOUSE
```

---

## Logitech PRO X Wireless Gaming Headset

### Status

Detection Only.

### Current Capabilities

* Device discovery
* Device identification

### Planned Capabilities

* Battery information
* Firmware information
* Equalizer information
* Sidetone information

---

## Wraith W75

### Status

Detection Only.

### Current Capabilities

* Device discovery
* Device identification

### Planned Capabilities

* Keyboard layout detection
* RGB control
* Multimedia key handling
* Vendor protocol research

---

## Adding a New Device

To add a new device:

1. Connect the device.
2. Run PeripheralOS.
3. Capture VID/PID and device name.
4. Add the device to the registry.
5. Mark support level accurately.
6. Document known capabilities.

Example registry entry:

```cpp
if (vendorId == 0x046d && productId == 0x40a8) {
    return {
        DeviceVendor::Logitech,
        DeviceKind::Mouse,
        "Logitech PRO 2 LIGHTSPEED",
        "logitech-pro-2-lightspeed",
        true
    };
}
```

---

## Device Support Policy

PeripheralOS must never claim full support unless the feature has been tested on real hardware.

Support claims must distinguish between:

* Detection
* Read-only functionality
* Writable functionality
* Stable daily-use functionality
