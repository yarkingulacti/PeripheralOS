# PeripheralOS Roadmap

This document describes the planned release roadmap for PeripheralOS.

The roadmap is expected to evolve as hardware support expands.

---

## Versioning

PeripheralOS follows Semantic Versioning.

Format:

```text
vMAJOR.MINOR.PATCH-suffix
````

Examples:

```text
v0.1.0-alpha
v0.2.0-alpha
v0.3.0-beta
v1.0.0
```

---

## Release Philosophy

PeripheralOS releases are milestone-driven.

Each release should deliver one clear layer of functionality.

Alpha releases may be incomplete and experimental.

Stable releases must be suitable for daily use.

---

## v0.1.0-alpha

### Status

Released.

### Focus

Initial working proof-of-concept.

### Completed

* Project structure
* Cross-platform CMake configuration
* Linux HID discovery
* Linux hidraw enumeration
* Device identification
* Logitech HID++ 2.0 transport
* HID++ feature discovery
* Logitech PRO 2 LIGHTSPEED detection
* Logitech HID++ device name reading
* GitHub Actions release workflow
* Linux, Windows and macOS release artifacts

---

## v0.2.0-alpha

### Due Date

2026-06-30

### Focus

Battery and device information.

### Goals

* Logitech HID++ UNIFIED_BATTERY support
* Battery percentage reading
* Battery status reading
* Charging state detection
* Firmware information reading
* Device serial number reading
* Model ID reading
* Unit ID reading
* Device capability discovery
* Improved runtime diagnostics

### Success Criteria

PeripheralOS can identify a Logitech PRO 2 LIGHTSPEED and display:

* Device name
* Battery percentage
* Battery status
* Firmware version
* Serial number
* Device identifiers

### Target Device

* Logitech PRO 2 LIGHTSPEED

---

## v0.3.0-alpha

### Due Date

2026-07-31

### Focus

Performance configuration.

### Goals

* DPI reading
* DPI configuration
* Polling rate reading
* Polling rate configuration
* Lift-off distance reading
* Sensor information support
* Safe writable HID++ commands
* Runtime confirmation before modifying device settings

### Success Criteria

Users can read and modify core mouse performance settings.

Expected functionality:

```bash
peripheralos dpi get
peripheralos dpi set 1600
peripheralos polling-rate get
peripheralos polling-rate set 1000
```

---

## v0.4.0-alpha

### Due Date

2026-08-31

### Focus

RGB and profile system.

### Goals

* RGB state reading
* RGB configuration
* RGB effects
* RGB synchronization
* Onboard profile detection
* Profile switching
* Profile persistence
* JSON profile storage

### Success Criteria

PeripheralOS can manage lighting and onboard profiles for supported devices.

Expected functionality:

```bash
peripheralos rgb get
peripheralos rgb set static --color "#00ffcc"
peripheralos profile list
peripheralos profile activate fps
```

---

## v0.5.0-alpha

### Due Date

2026-10-01

### Focus

Automation and daemon.

### Goals

* PeripheralOS daemon
* Configuration persistence
* Profile manager
* Device monitoring
* Device hotplug support
* Event system
* Runtime config directory
* Basic IPC channel

### Success Criteria

PeripheralOS can automatically manage connected devices without manual interaction.

Expected functionality:

* Device hotplug detection
* Background battery monitoring
* Automatic profile application
* Config persistence

---

## v0.6.0-alpha

### Due Date

2026-11-15

### Focus

Graphical user interface.

### Goals

* Qt 6 application
* Device dashboard
* Battery monitoring UI
* RGB editor
* DPI editor
* Profile editor
* Settings page
* Logs/diagnostics page

### Success Criteria

Users can manage supported devices entirely through a graphical interface.

---

## v1.0.0

### Due Date

2027-01-31

### Focus

First stable release.

### Goals

* Stable Linux backend
* Stable Logitech HID++ implementation
* Device profile system
* Per-game profile switching
* Plugin architecture foundation
* Complete documentation
* Public contributor onboarding
* Release-quality packaging
* User-facing installation instructions

### Success Criteria

PeripheralOS is production-ready for daily use on Linux and supports a complete Logitech workflow.

---

## Future Releases

Future versions may include:

* Windows runtime backend
* macOS runtime backend
* More Logitech devices
* Wraith keyboard support
* SteelSeries support
* Razer support
* Corsair support
* Plugin SDK
* Community device database
* Cloud profile sync
