# AGENTS.md

Guidelines for AI coding agents working on the PeripheralOS repository.

This file is intended for IDE-based and terminal-based coding agents that can read, edit, create, delete, refactor,
build, test or run code in this repository.

Examples include Codex, Cursor, JetBrains AI Assistant, Continue, Claude Code and similar tools.

---

## Project Summary

PeripheralOS is an open-source cross-platform peripheral management platform.

It is intended to become a modern alternative to vendor-locked peripheral software such as Logitech G HUB, Razer Synapse
and SteelSeries GG.

Primary technical context:

* Language: C++20
* Build system: CMake + Ninja
* Target platforms:

    * Linux
    * Windows
    * macOS
* Current primary development platform: Linux
* Current protocol focus: Logitech HID++ 2.0
* Current active milestone: v0.2.0-alpha
* Current primary validation device: Logitech PRO 2 LIGHTSPEED

Primary validation device:

```text
Device: Logitech PRO 2 LIGHTSPEED
Vendor ID: 046d
Product ID: 40a8
```

---

## Agent Role

Act as a careful senior C++ systems engineer.

Prioritize:

1. Hardware safety
2. Correct protocol behavior
3. Clean architecture
4. Small reviewable patches
5. Runtime validation
6. Documentation accuracy
7. Long-term maintainability

Do not behave like an autonomous bulk code generator.

---

## Repository Scope

Expected repository structure:

```text
include/
src/
docs/
.github/
tests/
README.md
CHANGELOG.md
CMakeLists.txt
AGENTS.md
```

Do not create new top-level directories unless the task clearly requires it.

---

## Current Milestone Context

The active milestone is:

```text
v0.2.0-alpha
```

Current milestone focus:

* Battery support
* Battery charging state detection
* Battery discharging state detection
* Full battery state detection
* Firmware information
* Serial number support
* Device capability discovery

Current completed or partially completed HID++ work:

* HID++ 2.0 transport
* HID++ feature discovery
* DEVICE_NAME support
* Device name retrieval
* UNIFIED_BATTERY feature discovery
* Battery packet retrieval
* Battery percentage parsing
* BatteryInfo API

Known battery limitation:

```text
Battery percentage is implemented.
Battery status mapping is not fully resolved.
Charging/discharging/full state detection must remain unverified until confirmed through hardware validation.
```

Do not claim battery status detection is complete unless runtime and hardware validation prove it.

---

## Core Architecture Rules

Shared core logic must remain platform-independent.

Allowed in shared logic:

```cpp
DeviceManager
PeripheralDevice
BatteryInfo
FirmwareInfo
SerialNumberInfo
DeviceCapability
Profile
```

Not allowed in shared logic:

```cpp
open("/dev/hidraw0");
SetupDiGetClassDevs();
IOHIDManagerCreate();
```

Platform-specific code must be isolated.

Preferred layout:

```text
src/platform/linux/
src/platform/windows/
src/platform/macos/
```

Linux-specific code must not leak into shared abstractions.

Windows and macOS support should be possible later without rewriting the core architecture.

---

## Device Abstraction Rules

Prefer vendor-neutral models.

Good:

```cpp
BatteryInfo
FirmwareInfo
SerialNumberInfo
DeviceCapability
```

Avoid unless strictly required:

```cpp
LogitechBatteryInfo
LogitechFirmwareInfo
LogitechSerialNumberInfo
```

Vendor-specific protocol details should stay behind common interfaces.

Public APIs should expose typed information, not raw HID++ packets.

---

## C++ Rules

Use C++20.

Prefer:

* RAII
* `std::optional`
* `std::unique_ptr`
* `std::vector<std::uint8_t>` for byte buffers
* `enum class`
* `const` correctness
* Explicit ownership
* Explicit error handling
* Small focused functions
* Clear parser boundaries

Avoid:

* Raw owning pointers
* Global mutable state
* Magic numbers without named constants
* Silent failures
* Catch-all exception handling without context
* Returning fake default values
* Large unrelated refactors
* Formatting-only changes mixed with functional changes

---

## HID++ Safety Rules

PeripheralOS currently targets Logitech HID++ 2.0.

For all HID++ work:

* Prefer read-only behavior first.
* Never add write commands unless explicitly requested.
* Never modify firmware, onboard memory, DPI profiles, RGB profiles or pairing state.
* Never send reset, bootloader or persistent configuration commands unless explicitly approved.
* Never assume protocol meaning from a single byte.
* Never expose unverified protocol interpretation through public APIs.

Allowed:

```text
statusByte = 0x01
Meaning = Unknown
```

Not allowed:

```text
statusByte = 0x01 means Charging
```

unless this is experimentally verified and documented.

Use these labels when needed:

```text
Unknown
Hypothesis
Possible interpretation
Unverified assumption
Experimental
Verified
Confirmed
```

---

## HID++ Feature Workflow

Every HID++ feature must follow this workflow:

1. Discover feature index.
2. Read raw packet data.
3. Document raw packets exactly.
4. Identify packet structure.
5. Mark unknown fields as unknown.
6. Validate packet size.
7. Validate packet format.
8. Detect HID++ error packets.
9. Reject malformed packets safely.
10. Create parser.
11. Create typed model.
12. Expose public API.
13. Add or update CLI output if required.
14. Runtime validate.
15. Hardware validate.
16. Update documentation.
17. Update CHANGELOG.md when user-facing behavior changes.

Successful compilation is not enough.

---

## HID++ Parser Rules

Every HID++ parser must:

* Validate minimum packet size.
* Validate expected response format.
* Detect HID++ error responses.
* Avoid out-of-bounds reads.
* Preserve unknown fields as unknown.
* Return safe failure when data is malformed.
* Avoid interpreting unknown bytes as final truth.

Parser tests should cover:

* Valid packet
* Too-short packet
* Malformed packet
* HID++ error packet
* Unknown status values

---

## Battery-Specific Rules

Current target issue area:

```text
Battery status and charging state detection
```

Expected final user-facing output example:

```text
Battery: 31% (Charging)
```

Rules:

* Battery percentage support already exists.
* Battery status mapping is unresolved unless proven otherwise.
* Charging state must not be guessed.
* Discharging state must not be guessed.
* Full battery state must not be guessed.
* Unknown status bytes must remain unknown.
* If a raw status byte is observed, document it before interpreting it.
* If interpretation is uncertain, expose `Unknown` rather than a false status.

Preferred model direction:

```cpp
enum class BatteryState {
    Unknown,
    Charging,
    Discharging,
    Full
};
```

Only add states that can be supported safely.

---

## Runtime Output Rules

CLI output should be concise and user-facing.

Good:

```text
Device Name: PRO 2 LIGHTSPEED
Battery: 31% (Charging)
Firmware: x.x.x
```

Acceptable during investigation only:

```text
Raw packet: 11 01 07 01 0F 0F 01 00 00 00 00 00
```

Before marking work complete, remove temporary debug output unless it is intentionally documented.

Do not leave parser traces, raw dumps or experimental diagnostics in normal production output.

---

## Documentation Rules

Documentation is part of the implementation.

When functionality changes, update the relevant files:

```text
README.md
CHANGELOG.md
docs/hidpp-notes.md
docs/device-support.md
docs/roadmap.md
docs/architecture.md
```

Do not document unimplemented behavior as complete.

For HID++ discoveries, update:

```text
docs/hidpp-notes.md
```

Minimum HID++ documentation format:

```text
Device:
Vendor ID:
Product ID:

Feature:
Function:

Observed Packet:

Interpretation:

Validation Status:
```

Validation status must be one of:

```text
Experimental
Verified
Confirmed
```

Definitions:

```text
Experimental: Observed once, not fully verified.
Verified: Observed multiple times with consistent behavior.
Confirmed: Observed across devices or considered production-safe.
```

---

## GitHub Project Rules

GitHub is the source of truth for project planning.

The following must remain synchronized:

* GitHub Issues
* GitHub Milestones
* GitHub Project Board
* Roadmap documentation
* CHANGELOG.md
* Release notes

Preferred tool:

```bash
gh
```

Do not assume issue numbers.

Before starting issue-based work:

1. Verify the issue exists.
2. Verify the issue title.
3. Verify milestone assignment.
4. Verify project board status.
5. Verify acceptance criteria.

Useful commands:

```bash
gh issue view <number>
gh issue list --milestone "v0.2.0-alpha"
gh milestone list
gh project list
gh project item-list
```

If GitHub access is unavailable, say so clearly.

---

## Issue Ownership Rules

Every implementation task must belong to exactly one GitHub issue.

Do not mix multiple issues in one patch.

Good:

```text
feature/battery-status-detection
```

Bad:

```text
feature/battery-firmware-serial-refactor
```

If multiple issues are related, implement them separately.

---

## Branch Naming

Use focused branch names.

Features:

```text
feature/<topic>
```

Examples:

```text
feature/battery-status-detection
feature/firmware-information
feature/device-capability-discovery
```

Fixes:

```text
fix/<topic>
```

Examples:

```text
fix/hidpp-response-parser
fix/linux-device-filter
```

Documentation:

```text
docs/<topic>
```

Examples:

```text
docs/hidpp-battery-notes
docs/device-support-update
```

---

## Commit Rules

Do not commit automatically unless explicitly asked.

When asked to commit, use Conventional Commits.

Good examples:

```text
feat(hidpp): detect unified battery status byte
feat(device): expose battery charging state
fix(hidpp): reject malformed battery responses
docs(hidpp): document unified battery observations
refactor(core): introduce battery state enum
```

Bad examples:

```text
update
fix
changes
battery
stuff
```

Prefer small logical commits.

Before committing, inspect:

```bash
git status
git diff
```

---

## Build Rules

Use the smallest relevant build command.

Preferred debug build command:

```bash
cmake --build cmake-build-debug
```

Known local binary path:

```bash
/home/yarkin/workspace/projelerim/PeripheralOS/cmake-build-debug/bin/peripheralos
```

If the build directory differs, inspect the repository and adapt.

Do not claim the build passed unless it was actually run.

If the build was not run, say:

```text
Build not run.
```

---

## Runtime Validation Rules

A successful build does not mean the implementation is complete.

Runtime validation should check:

* Device discovery
* HID++ feature discovery
* Packet retrieval
* Parser result
* Error handling path
* CLI output
* Behavior on the real target device

Preferred runtime command:

```bash
/home/yarkin/workspace/projelerim/PeripheralOS/cmake-build-debug/bin/peripheralos
```

If hardware validation was not performed, say:

```text
Hardware validation not performed.
```

Do not mark issue complete without hardware validation when HID++ behavior changed.

---

## Definition of Done

An issue is complete only when all are true:

* Code implemented
* Build successful
* Runtime verified
* Hardware tested
* Documentation updated
* CHANGELOG.md updated
* Issue requirements satisfied
* GitHub Project status updated
* Ready for merge

If any item is missing, the issue is not done.

---

## Agent Output Format

After making changes, report in this format:

```text
Changed files:
- ...

What changed:
- ...

Validation:
- Build: ...
- Runtime: ...
- Hardware: ...
- Docs: ...

Remaining:
- ...

Suggested commit:
- ...
```

If validation could not be run, state that clearly.

Do not hide uncertainty.

---

## Scope Control

Only edit files directly related to the task.

Allowed for battery status work:

```text
BatteryInfo model
HID++ battery parser
HID++ client method
CLI output for battery info
docs/hidpp-notes.md
docs/device-support.md
CHANGELOG.md
tests related to battery parsing
```

Not allowed unless explicitly requested:

```text
Repository-wide formatting
Unrelated class renaming
Large architecture rewrites
Global CMake restructuring
GUI implementation
Windows backend implementation
macOS backend implementation
Unrelated firmware or serial work
```

---

## Dependency Rules

Do not introduce new dependencies unless necessary.

Before adding a dependency, explain:

* Why it is needed
* Why standard library support is insufficient
* Cross-platform impact
* Build impact
* Maintenance impact

Prefer the C++ standard library where practical.

---

## Testing Rules

If a test structure exists, add or update focused tests.

For parser changes, test:

* Valid packets
* Short packets
* Malformed packets
* HID++ error packets
* Unknown values

Do not add large test frameworks without explicit approval.

---

## Release Rules

PeripheralOS uses semantic versioning.

Examples:

```text
v0.1.0-alpha
v0.2.0-alpha
v0.3.0-beta
v1.0.0
```

Do not invent release notes.

Release notes must be based on actual implemented, validated and documented work.

---

## Prohibited Agent Behavior

Do not:

* Invent HID++ protocol meanings.
* Claim hardware validation without running on hardware.
* Claim build success without running the build.
* Change unrelated files.
* Perform broad automatic refactors.
* Add write/device-control commands during read-only research.
* Mix multiple GitHub issues in one change.
* Silently change public APIs.
* Silently change CLI output format.
* Leave temporary debug logs in production output.
* Update roadmap without syncing GitHub planning.
* Close GitHub issues before Definition of Done is satisfied.

---

## Preferred Task Footer

When receiving a task, follow this default behavior:

```text
Follow AGENTS.md.
Keep the patch minimal.
Do not touch unrelated files.
Do not invent HID++ protocol meanings.
Prefer read-only hardware-safe implementation.
After changes, report changed files, validation commands, runtime result, docs updated and suggested commit message.
```
