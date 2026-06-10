# Coding Standards

This document describes coding standards for PeripheralOS.

---

## Language Standard

PeripheralOS uses:

```text
C++20
````

All code should be compatible with:

* GCC
* Clang
* AppleClang
* MSVC

---

## General Principles

Prefer:

* Clear ownership
* RAII
* Small functions
* Explicit error handling
* Platform abstraction
* Testable logic
* Safe defaults

Avoid:

* Global mutable state
* Raw owning pointers
* Silent failures
* Unclear ownership
* Platform-specific logic in core modules
* Overly clever template code

---

## File Organization

Recommended structure:

```text
include/peripheralos/
├── core/
├── devices/
├── logitech/
├── platform/
├── profiles/
└── rgb/

src/
├── core/
├── devices/
├── logitech/
├── platform/
├── profiles/
└── rgb/
```

Headers should live under:

```text
include/peripheralos/
```

Source files should live under:

```text
src/
```

---

## Naming

### Classes

Use PascalCase.

```cpp
class DeviceManager;
class HidDevice;
class LogitechDevice;
```

### Functions

Use camelCase.

```cpp
void discoverDevices();
bool openDevice();
```

### Variables

Use camelCase.

```cpp
std::string deviceName;
int pollingRate;
```

### Constants

Use PascalCase for constants.

```cpp
constexpr int DefaultPollingRate = 1000;
```

### Enums

Use `enum class`.

```cpp
enum class DeviceKind {
    Unknown,
    Mouse,
    Keyboard,
    Headset
};
```

---

## Ownership

Use `std::unique_ptr` by default.

Use `std::shared_ptr` only when ownership is truly shared.

Avoid raw owning pointers.

Allowed:

```cpp
std::unique_ptr<Device> device;
```

Avoid:

```cpp
Device* device = new Device();
```

---

## Error Handling

Preferred:

```cpp
std::optional<T>
```

Future preferred:

```cpp
std::expected<T, Error>
```

Exceptions may be used for fatal initialization errors.

Avoid throwing exceptions from low-level packet parsing unless the failure is unrecoverable.

---

## Platform Code

Platform-specific code must be isolated.

Allowed:

```text
src/platform/linux/
src/platform/windows/
src/platform/macos/
```

Not allowed:

```cpp
#ifdef __linux__
open("/dev/hidraw0", O_RDWR);
#endif
```

inside core business logic.

---

## HID Communication Rules

HID code must be careful.

Rules:

* Prefer read-only commands first.
* Validate response size before indexing.
* Filter unrelated input reports.
* Never assume a device supports a feature.
* Treat HID++ error packets as errors.
* Avoid write commands until packet format is understood.
* Do not require root for normal usage if avoidable.

---

## Logging

Logs should help debugging but must avoid noise.

Log categories planned:

* Core
* Device
* HID
* Logitech HID++
* Platform
* Profile
* RGB
* Daemon
* UI

Sensitive information should not be logged unless explicitly needed.

---

## Commit Convention

Use Conventional Commits.

Examples:

```text
feat(hidpp): add unified battery feature discovery
feat(device): add firmware information model
fix(linux): filter non-HID++ input reports
docs(roadmap): update v0.2.0-alpha goals
ci(release): improve artifact packaging
refactor(core): introduce device capability model
```

---

## Pull Request Expectations

Before opening a pull request:

* Build the project
* Run tests if available
* Update documentation if behavior changed
* Keep pull requests focused
* Explain hardware tested

Example PR description:

````md
## Summary

Adds Logitech UNIFIED_BATTERY feature discovery.

## Tested Hardware

- Logitech PRO 2 LIGHTSPEED

## Test Output

```text
HID++ UNIFIED_BATTERY feature index: 7
````

## Checklist

* [ ] Builds locally
* [ ] Tested on hardware
* [ ] Documentation updated

```

---

## Documentation Rules

Documentation should be updated when:

- New devices are added
- New features are implemented
- Milestones change
- Release process changes
- Platform support changes
- Runtime behavior changes

---

## Security Rules

PeripheralOS interacts with HID devices.

Important:

- Do not execute external commands based on device input.
- Do not load untrusted plugins.
- Do not parse untrusted config without validation.
- Do not write to device memory unless the operation is understood.
- Prefer safe read-only exploration during early development.
