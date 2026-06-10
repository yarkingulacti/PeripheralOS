# PeripheralOS Architecture

PeripheralOS is designed as a cross-platform peripheral management platform.

The long-term goal is to provide a unified alternative to vendor-locked software such as Logitech G HUB, Razer Synapse,
SteelSeries GG and similar tools.

---

## Design Goals

PeripheralOS is built around the following goals:

- Cross-platform support
- Clean hardware abstraction
- Vendor-independent device model
- Safe HID communication
- Modular feature implementation
- Testable core logic
- Future daemon support
- Future graphical user interface
- Long-term plugin architecture

---

## High-Level Architecture

```text
PeripheralOS
│
├── CLI
├── Daemon
├── UI
│
├── Core
├── Device Manager
├── Device Registry
├── Profile Engine
├── Macro Engine
├── RGB Engine
│
├── HID Layer
├── Vendor Layers
│   ├── Logitech HID++
│   ├── Wraith
│   ├── SteelSeries
│   ├── Razer
│   └── Generic HID
│
├── Platform Backends
│   ├── Linux
│   ├── Windows
│   └── macOS
│
└── Plugins
````

---

## Current v0.1.0-alpha Architecture

The current implementation focuses on the first functional Linux prototype.

```text
main.cpp
│
├── LinuxHidDiscovery
│   └── Enumerates /dev/hidraw* devices
│
├── DeviceIdentity
│   └── Identifies known devices by VID/PID/name
│
├── LinuxHidDevice
│   └── Opens hidraw device file
│
└── Hidpp20Client
    └── Performs Logitech HID++ 2.0 communication
```

---

## Core Layer

The Core layer will contain platform-independent business logic.

Responsibilities:

* Device abstraction
* Profile management
* Capability representation
* Feature routing
* Error handling
* Runtime configuration
* Logging integration
* Event dispatching

The Core layer must not directly call platform APIs.

Allowed:

```cpp
DeviceManager manager;
Profile profile;
BatteryInfo battery;
```

Not allowed:

```cpp
open("/dev/hidraw7", O_RDWR);
SetupDiGetClassDevs(...);
IOHIDManagerCreate(...);
```

---

## Device Manager

The Device Manager is responsible for discovering and tracking devices.

Planned responsibilities:

* Discover devices
* Detect hotplug events
* Map raw HID devices to high-level peripherals
* Track supported and unsupported devices
* Expose device capabilities
* Route device commands

Example future model:

```cpp
class DeviceManager {
public:
    std::vector<PeripheralDevice> discover();
    std::optional<PeripheralDevice> findById(DeviceId id);
};
```

---

## Device Registry

The Device Registry maps hardware identifiers to known devices.

Current examples:

```text
046d:40a8 -> Logitech PRO 2 LIGHTSPEED
046d:c543 -> Logitech LIGHTSPEED Receiver
046d:0aba -> Logitech PRO X Wireless Gaming Headset
2e3c:c365 -> Wraith W75
```

The registry should define:

* Vendor
* Device name
* Device kind
* Support level
* Supported protocols
* Supported capabilities

---

## Device Capability Model

PeripheralOS should not assume that all devices support all features.

Each device should expose capabilities.

Examples:

```text
Battery
DPI
Polling Rate
RGB
Profiles
Macros
Firmware Info
Serial Number
```

Example future API:

```cpp
if (device.hasCapability(DeviceCapability::Battery)) {
    auto battery = device.getBatteryInfo();
}
```

---

## HID Layer

The HID layer provides low-level communication with devices.

Responsibilities:

* Open device
* Close device
* Read packets
* Write packets
* Handle platform-specific transport
* Apply timeout logic
* Filter unrelated reports
* Provide safe error handling

The HID layer should not know about high-level features like DPI or RGB.

---

## Vendor Layers

Vendor layers implement protocol-specific logic.

### Logitech HID++

Current target:

* Logitech HID++ 2.0
* Logitech PRO 2 LIGHTSPEED
* HID++ feature discovery
* DEVICE_NAME support
* UNIFIED_BATTERY support planned

Future target:

* DPI
* Polling rate
* RGB
* Onboard profiles
* Firmware info
* Serial number

---

## Platform Backends

### Linux

Current backend:

* `hidraw`
* `libudev`

Responsibilities:

* Enumerate `/dev/hidraw*`
* Read sysfs metadata
* Parse `uevent`
* Open HID device node
* Read/write HID reports

### Windows

Planned backend:

* SetupAPI
* HID API
* RawInput

Responsibilities:

* Enumerate HID devices
* Open device handles
* Read/write HID reports
* Detect hotplug events

### macOS

Planned backend:

* IOKit
* CoreFoundation

Responsibilities:

* Enumerate HID devices
* Open HID interfaces
* Read/write HID reports
* Detect hotplug events

---

## CLI

Current CLI behavior:

* Prints runtime metadata
* Lists HID devices
* Identifies supported devices
* Opens supported Logitech device
* Reads HID++ device name

Future CLI commands:

```bash
peripheralos devices
peripheralos device info
peripheralos battery
peripheralos dpi get
peripheralos dpi set 1600
peripheralos polling-rate get
peripheralos polling-rate set 1000
```

---

## Daemon

The daemon is planned for later releases.

Responsibilities:

* Background device monitoring
* Profile switching
* Per-game automation
* Hotplug handling
* Persistent configuration
* IPC communication with UI/CLI

Possible IPC options:

* DBus on Linux
* Named pipes on Windows
* XPC or local socket on macOS
* Cross-platform local socket abstraction

---

## UI

Qt 6 is planned for the first graphical interface.

Planned screens:

* Device dashboard
* Battery monitor
* DPI editor
* Polling rate editor
* RGB editor
* Profile editor
* Settings page
* Logs/diagnostics view

---

## Error Handling

PeripheralOS should use explicit, recoverable error handling.

Preferred:

```cpp
std::optional<T>
std::expected<T, Error> // when available or polyfilled
```

Avoid:

* Silent failures
* Raw integer error codes without context
* Throwing exceptions across module boundaries unnecessarily

---

## Logging

Logging should eventually support:

* Console logs
* File logs
* Debug-level HID packet logs
* Runtime diagnostics
* User-friendly error reporting

Sensitive data should never be logged unless explicitly required for debugging.

---

## Security Considerations

PeripheralOS interacts with input devices and HID interfaces.

Important principles:

* Least privilege
* Read-only operations first
* Avoid arbitrary command execution
* Validate all external configuration
* Avoid unsafe plugin loading
* Clearly document udev permission requirements
* Never require root for normal runtime if avoidable

---

## Current Architecture Status

| Area                     | Status      |
|--------------------------|-------------|
| Linux HID discovery      | Implemented |
| Device identification    | Implemented |
| Logitech HID++ transport | Implemented |
| HID++ device name        | Implemented |
| Battery info             | Planned     |
| DPI                      | Planned     |
| Polling rate             | Planned     |
| RGB                      | Planned     |
| Daemon                   | Planned     |
| Qt UI                    | Planned     |
| Windows backend          | Planned     |
| macOS backend            | Planned     |
