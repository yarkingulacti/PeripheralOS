# PeripheralOS Agent Instructions

This document defines the rules that AI coding agents, IDE agents, code-editing assistants, refactoring tools, and automated development helpers must follow when working on the PeripheralOS repository.

PeripheralOS is an open-source, cross-platform peripheral management platform written in C++20 and built with CMake + Ninja.

The agent's goal is not to produce code quickly. The goal is to produce safe, maintainable, cross-platform, well-documented, hardware-validated engineering work.

---

## 1. Output Language Rule

All agent-generated outputs for this project must be written in English by default.

This includes:

- Code comments
- Documentation
- Commit messages
- Pull request descriptions
- Issue comments
- Changelog entries
- Release notes
- Implementation summaries
- Review comments
- Validation reports
- CLI-facing text unless explicitly localized later

Do not generate Turkish project artifacts unless the user explicitly requests Turkish for a specific output.

---

## 2. Project Identity

Project name:

- PeripheralOS

Project type:

- Open-source cross-platform peripheral management platform

Purpose:

- PeripheralOS aims to provide a modern, open-source alternative to vendor-locked peripheral software such as Logitech G HUB, Razer Synapse, SteelSeries GG, and similar tools.

Primary language:

- C++20

Build system:

- CMake + Ninja

Target platforms:

- Linux
- Windows
- macOS

Current primary development platform:

- Linux

Current primary validation device:

- Logitech PRO 2 LIGHTSPEED
- Vendor ID: 046d
- Product ID: 40a8

---

## 3. Agent Role

The agent must act like a senior systems engineer.

The agent is responsible for:

- Preserving cross-platform architecture.
- Keeping shared core logic platform-independent.
- Isolating OS-specific code into platform backends.
- Avoiding unverified HID++ assumptions.
- Treating hardware safety as mandatory.
- Keeping implementation work tied to verified GitHub issues.
- Updating documentation and changelog when behavior changes.
- Suggesting validation steps after implementation.
- Producing small, logical, reviewable changes.
- Explaining tradeoffs when architecture decisions are involved.

The agent must not treat a successful build as proof that the task is complete.

---

## 4. Non-Negotiable Rules

The following rules are mandatory:

1. Shared core logic must not directly depend on operating system APIs.
2. HID++ protocol meanings must never be invented.
3. Read-only support must exist before write functionality is introduced.
4. Hardware-modifying commands must be avoided unless packet behavior is understood and documented.
5. Every HID++ feature must be runtime validated.
6. Every HID++ feature must be hardware validated.
7. Temporary debug output must not remain in production-facing output.
8. Every implementation task must belong to exactly one verified GitHub issue.
9. Issue numbers must never be assumed.
10. Documentation and changelog updates are part of the implementation.
11. Release notes must only describe completed and verified work.
12. Agent outputs must be English by default.

---

## 5. Repository Structure

Expected repository structure:

```text
include/
src/
docs/
.github/
tests/
CMakeLists.txt
README.md
CHANGELOG.md
```

Platform-specific code should be isolated under:

```text
src/platform/linux/
src/platform/windows/
src/platform/macos/
```

Shared business logic must not call platform APIs directly.

Allowed in shared/core code:

```cpp
DeviceManager
PeripheralDevice
BatteryInfo
FirmwareInfo
SerialNumberInfo
DeviceCapability
Profile
Hidpp20Client
```

Avoid in shared/core code:

```cpp
open("/dev/hidraw0");
ioctl(...);
SetupDiGetClassDevs(...);
IOHIDManagerCreate(...);
```

Those belong in platform-specific backends only.

---

## 6. Architecture Principles

Every change must be evaluated using these priorities:

1. Cross-platform design
2. Clean architecture
3. Device abstraction
4. Hardware safety
5. Maintainability
6. Readability
7. Testability
8. Documentation quality

Architecture quality is more important than short-term implementation speed.

Do not introduce a quick fix that damages long-term maintainability.

---

## 7. Layering Rules

PeripheralOS should conceptually follow this layering:

```text
Application / CLI
Core domain models
Device abstraction
Vendor protocol layer
Transport layer
Platform backend
Operating system APIs
Hardware
```

Rules:

- CLI code should use public APIs.
- Core domain models should be vendor-neutral.
- Vendor-specific protocol details should remain behind abstractions.
- Transport code should handle packet send/receive behavior.
- Parser code must validate incoming data.
- Platform backends should contain OS-specific APIs.
- Shared layers must not include Linux, Windows, or macOS system calls directly.

---

## 8. Device Abstraction Rules

Prefer vendor-neutral abstractions.

Prefer:

```cpp
BatteryInfo
FirmwareInfo
SerialNumberInfo
DeviceCapability
DeviceIdentity
PeripheralDevice
```

Avoid unless strictly required:

```cpp
LogitechBatteryInfo
LogitechFirmwareInfo
LogitechSerialNumberInfo
```

Vendor-specific behavior should be hidden behind common interfaces.

Preferred shape:

```cpp
class PeripheralDevice {
public:
    virtual std::optional<BatteryInfo> readBatteryInfo() = 0;
    virtual std::optional<FirmwareInfo> readFirmwareInfo() = 0;
};
```

Logitech HID++ implementations should remain behind these interfaces.

---

## 9. HID++ Development Rules

PeripheralOS currently targets Logitech HID++ 2.0.

Every new HID++ feature must follow this workflow:

1. Discover feature index.
2. Read raw packet.
3. Document raw packet.
4. Identify packet structure.
5. Implement parser.
6. Create typed model.
7. Expose public API.
8. Add runtime output if needed.
9. Runtime validate.
10. Hardware validate.
11. Update documentation.

No step may be skipped.

---

## 10. HID++ Discovery Workflow

Every feature must start with feature index discovery.

Example features:

- UNIFIED_BATTERY
- DEVICE_NAME
- DEVICE_FW_VERSION

Before implementation, verify:

- Feature ID
- Feature index
- Supported / unsupported result
- Raw request packet
- Raw response packet
- Possible error response

Findings must be documented immediately.

---

## 11. Raw Packet Documentation

Raw packet observations must be documented exactly as observed before interpretation.

Use this format:

```text
Device:
Vendor ID:
Product ID:

Feature:
Function:

Request Packet:
Response Packet:
Error Packet:

Observed Behavior:
Interpretation:
Validation Status:
```

Unknown fields must remain unknown.

Allowed:

```text
response[4] = battery percentage
response[5] = unknown
response[6] = unknown
```

Not allowed unless experimentally verified:

```text
response[5] = charging state
```

---

## 12. Reverse Engineering Rules

Never invent protocol meanings.

Allowed wording:

- Hypothesis
- Possible interpretation
- Unverified assumption
- Unknown field
- Observed but not confirmed

Not allowed unless verified:

```text
statusByte = 1 means charging
```

Production APIs must not expose unverified protocol interpretations.

Wrong:

```cpp
BatteryStatus::Charging
```

if based on an unverified byte value.

Correct:

```cpp
BatteryStatus::Unknown
```

until the mapping is validated.

---

## 13. Parser Safety Rules

Every parser must validate:

- Packet size
- Report ID
- Device index
- Feature index
- Function ID
- HID++ error packet format
- Malformed packets
- Unexpected packets
- Unsupported features
- Invalid arguments
- Timeout or missing response

Never trust incoming device data.

Prefer:

```cpp
std::optional<BatteryInfo> parseBatteryResponse(const HidppResponse& response);
```

Better if the project has or introduces an explicit result type:

```cpp
Result<BatteryInfo, HidppError>
```

Avoid unsafe parser signatures:

```cpp
BatteryInfo parse(uint8_t* data);
```

---

## 14. HID++ Error Handling

HID++ error responses must never be parsed as valid responses.

Handle these cases explicitly:

- Feature not supported
- Invalid function
- Invalid argument
- Unknown error
- Timeout
- Malformed response
- Unexpected feature index
- Unexpected function ID

Error details may be useful internally, but user-facing output should remain clean.

---

## 15. Hardware Safety Rules

Read-only support must always come first.

Before introducing write operations:

- Packet format must be understood.
- Hardware behavior must be documented.
- Failure modes must be known.
- A rollback strategy should exist.
- The command must not unexpectedly modify firmware, onboard memory, profiles, or pairing state.

Avoid commands that may:

- Modify firmware
- Change onboard memory
- Reset profiles
- Change DPI permanently
- Change polling rate permanently
- Enter bootloader mode
- Pair or unpair devices

Hardware safety takes priority over feature completeness.

---

## 16. Debug Output Rules

Temporary debug output is allowed during investigation.

Allowed during active research:

- Raw packet dumps
- Feature index dumps
- Parser traces
- Experimental diagnostics

Before marking work complete, remove:

- Temporary packet dumps
- Experimental parser logs
- Noisy CLI diagnostics
- Ad-hoc std::cout traces

Keep only user-facing runtime output.

Good:

```text
Device Name: PRO 2 LIGHTSPEED
Battery: 15%, status=unknown
Firmware: x.x.x
```

Bad outside active debugging:

```text
TX: 11 01 07 01 ...
RX: 11 01 07 01 ...
DEBUG parse byte[5] = 0x01
```

If debug output intentionally remains, document why.

---

## 17. Runtime Verification Rules

A successful build is not enough.

Every implementation should verify:

- CMake configure succeeds
- Build succeeds
- CLI runs
- Target device is detected
- Feature discovery works
- Expected runtime output appears
- Error paths behave safely
- Temporary debug output is removed

For HID++ features, also verify:

- Raw packet observed
- Parser output verified
- Hardware tested
- `docs/hidpp-notes.md` updated

---

## 18. Hardware Validation Rules

HID++ features are not complete without physical device validation.

Minimum validation record:

```text
Device:
Vendor:
Vendor ID:
Product ID:
Connection:
Platform:
Kernel / OS:
Feature:
Function:
Observed Packet:
Parsed Output:
Validation Status:
Notes:
```

Validation levels:

- Experimental: observed once, not verified
- Verified: observed multiple times on the same device
- Confirmed: observed across devices and considered production-safe

---

## 19. Active Milestone Context

Current milestone:

- v0.2.0-alpha

Status:

- Active Development

Primary objective:

- Expand Logitech HID++ support beyond device discovery.

Focus areas:

- Battery Support
- Firmware Information
- Serial Number Support
- Capability Discovery

Primary validation device:

- Logitech PRO 2 LIGHTSPEED
- Vendor ID: 046d
- Product ID: 40a8

Primary platform:

- Linux

Development order:

- Linux
- Windows
- macOS

Linux implementation must be designed so Windows and macOS backends can be added later without architectural rewrites.

---

## 20. Current Completed Context

The following are considered implemented in the current milestone context:

- Linux HID enumeration
- Linux hidraw discovery
- Device metadata collection
- HID++ 2.0 transport
- HID++ feature discovery
- DEVICE_NAME support
- Device name retrieval
- Logitech PRO 2 LIGHTSPEED detection
- UNIFIED_BATTERY feature discovery
- Battery packet retrieval
- Battery packet parsing
- Battery percentage reading
- BatteryInfo API

Known battery limitation:

- Charging state unresolved
- Battery status mapping unresolved

Do not mark charging, discharging, or full state as supported unless packet behavior has been validated.

---

## 21. Current Open Goals

### Firmware Information

Deliverables:

- DEVICE_FW_VERSION discovery
- Firmware packet retrieval
- Firmware parser
- FirmwareInfo model
- FirmwareInfo API
- CLI output
- Documentation update
- Hardware validation

### Serial Number Support

Deliverables:

- Feature discovery
- Serial packet retrieval
- Serial parser
- SerialNumberInfo model
- API exposure
- Documentation update
- Hardware validation

### Capability Discovery

Deliverables:

- Capability enumeration
- DeviceCapability abstraction
- Capability API
- Capability reporting
- Documentation update
- Hardware validation

### Battery Improvements

Deliverables:

- Charging state detection
- Discharging state detection
- Full battery state detection
- Battery status mapping
- Unified battery documentation update
- Hardware validation

Battery status mapping must remain `unknown` until validated.

---

## 22. GitHub Source of Truth

GitHub planning is the source of truth.

The following must remain synchronized:

- GitHub Issues
- GitHub Milestones
- GitHub Project Board
- `docs/roadmap.md`
- `CHANGELOG.md`
- Release Notes

Prefer GitHub CLI over manual GitHub UI instructions.

Preferred tool:

```bash
gh
```

---

## 23. Issue Rules

Implementation work must originate from a verified GitHub issue.

Before starting work, verify:

- Issue exists
- Issue title is correct
- Issue milestone is correct
- Issue project status is correct

Never assume issue numbers.

Do not say:

```text
Working on Issue #3
```

unless the issue was verified.

Use:

```bash
gh issue list
gh issue view <number>
```

Roadmap items are not implementation tasks. If a roadmap item has no GitHub issue, create or request an issue before implementation.

---

## 24. Issue Lifecycle

PeripheralOS issue lifecycle:

```text
Roadmap
-> Milestone
-> Issue
-> Ready
-> In Progress
-> Review
-> Testing
-> Done
```

Every implementation task must be linked to exactly one GitHub issue.

---

## 25. Project Board Workflow

Project:

- PeripheralOS Development

Allowed statuses:

- Backlog
- Ready
- In Progress
- Review
- Testing
- Done

Status meanings:

- Backlog: planned, not scheduled
- Ready: approved, can be started
- In Progress: active development
- Review: implementation complete, awaiting review
- Testing: runtime and hardware validation
- Done: merged, verified, documented

Expected transitions:

```text
Backlog -> In Progress
In Progress -> Review
Review -> Testing
Testing -> Done
```

The agent may suggest status transitions, but must not claim completion without validation.

---

## 26. Feature Ownership Rules

Every implementation must belong to exactly one issue.

Do not mix unrelated work in one branch.

Do not combine these into a single branch unless the verified issue explicitly requires it:

- Battery status detection
- Firmware information
- Serial number support
- Capability discovery

Branch examples:

- `feature/unified-battery-discovery`
- `feature/firmware-information`
- `feature/device-capability-discovery`
- `fix/hidpp-response-parser`
- `fix/linux-device-filter`
- `docs/device-support`
- `docs/roadmap-update`

---

## 27. Branch Rules

Feature branch:

```text
feature/<topic>
```

Bug fix branch:

```text
fix/<topic>
```

Documentation branch:

```text
docs/<topic>
```

Refactor branch:

```text
refactor/<topic>
```

CI branch:

```text
ci/<topic>
```

Examples:

- `feature/firmware-information`
- `feature/serial-number-support`
- `feature/capability-discovery`
- `fix/hidpp-error-packet-detection`
- `docs/hidpp-notes-update`
- `refactor/device-abstraction`

---

## 28. Definition of Done

An issue is not done until every applicable item is complete:

- [ ] Code implemented
- [ ] Build successful
- [ ] Runtime verified
- [ ] Hardware tested
- [ ] Documentation updated
- [ ] CHANGELOG updated
- [ ] Issue requirements satisfied
- [ ] Project status updated
- [ ] Ready for merge

Additional HID++ checklist:

- [ ] Feature index discovered
- [ ] Raw packet documented
- [ ] Parser validates packet size
- [ ] Parser detects HID++ error packets
- [ ] Typed model created
- [ ] Public API exposed
- [ ] Unknown fields marked as unknown
- [ ] Hardware validation recorded

---

## 29. Documentation Requirements

Code changes often require documentation changes.

Common documentation files:

- `README.md`
- `CHANGELOG.md`
- `docs/architecture.md`
- `docs/device-support.md`
- `docs/hidpp-notes.md`
- `docs/roadmap.md`

HID++ changes usually require:

- `docs/hidpp-notes.md`
- `docs/device-support.md`
- `CHANGELOG.md`
- `README.md`

Documentation must reflect actual implementation status.

Do not document:

```text
Charging state supported
```

if battery status mapping is unresolved.

Use:

```text
Battery percentage supported.
Battery status mapping currently unknown.
```

---

## 30. CHANGELOG Rules

Every user-visible or project-visible change should update `CHANGELOG.md`.

Use categories such as:

- Added
- Changed
- Fixed
- Documentation
- Internal

Example:

```md
## [Unreleased]

### Added

- Added HID++ firmware information discovery for supported Logitech devices.

### Documentation

- Documented observed DEVICE_FW_VERSION packets in HID++ notes.
```

Release notes must never be invented. They must be derived from completed project history.

---

## 31. Commit Convention

Use Conventional Commits.

Good examples:

- `feat(hidpp): discover firmware feature index`
- `feat(hidpp): parse firmware version response`
- `feat(device): expose firmware info api`
- `feat(cli): print firmware information`
- `fix(hidpp): reject malformed battery responses`
- `docs(hidpp): document unified battery packets`
- `docs(device): update supported device matrix`
- `refactor(core): introduce device capability model`
- `ci(build): improve cmake preset validation`

Avoid:

- `feat: update`
- `fix: bug`
- `changes`
- `battery support`

Each commit should represent one logical change.

---

## 32. Code Style Rules

Language:

- C++20

Naming:

Classes:

- `DeviceManager`
- `Hidpp20Client`
- `PeripheralDevice`
- `FirmwareInfo`

Functions:

- `discoverDevices()`
- `readBatteryInfo()`
- `readFirmwareInfo()`
- `parseBatteryResponse()`

Variables:

- `deviceName`
- `batteryPercentage`
- `featureIndex`
- `responsePacket`

Prefer:

- `std::unique_ptr`
- `std::optional`
- `std::variant`
- RAII
- Explicit ownership
- Const correctness
- Small functions
- Clear error handling

Avoid:

- Raw owning pointers
- Global mutable state
- Silent failures
- Magic numbers without explanation
- Platform APIs in core logic
- Large god classes

---

## 33. Error Handling Style

Silent failure is not acceptable.

Bad:

```cpp
return {};
```

without context.

Acceptable only when the caller can distinguish the reason elsewhere:

```cpp
return std::nullopt;
```

Preferred for protocol operations:

```cpp
Result<T, HidppError>
```

or an equivalent explicit error model.

Errors should preserve enough information for debugging without polluting user-facing output.

---

## 34. CMake Rules

CMake changes must be minimal and platform-aware.

Maintain:

- C++20 standard enforcement
- Ninja compatibility
- Linux build compatibility
- Future Windows/macOS compatibility
- Clear target structure
- Conditional platform-specific source inclusion

Avoid hardcoded local paths.

Bad:

```cmake
include_directories(/home/yarkin/...)
```

Good:

```cmake
target_include_directories(peripheralos PRIVATE include)
```

---

## 35. CLI Output Rules

CLI output should be concise and user-facing.

Good:

```text
Device Name: PRO 2 LIGHTSPEED
Battery: 15%, status=unknown
Firmware: x.x.x
```

Bad outside active debugging:

```text
TX: 11 01 07 01 ...
RX: 11 01 07 01 ...
DEBUG parse byte[5] = 0x01
```

Raw packet output is allowed only during active investigation or behind an intentional debug mode.

---

## 36. Testing Expectations

If test infrastructure exists, add tests for parser and model logic.

Prioritize tests for:

- Packet size validation
- Malformed packet rejection
- HID++ error packet detection
- Known valid response parsing
- Unknown field preservation
- Unsupported feature behavior

Parser tests should not require physical hardware.

Hardware validation remains a separate requirement.

---

## 37. Agent Workflow Before Editing Code

Before changing code, the agent should:

1. Verify the related GitHub issue.
2. Verify the milestone.
3. Inspect the current file structure.
4. Find existing patterns.
5. Plan the smallest safe change.
6. Check platform boundaries.
7. For HID++, check raw packet, parser, and documentation requirements.
8. Apply the code change.
9. Build and test when possible.
10. Provide runtime and hardware validation steps.
11. Update documentation and changelog when needed.
12. Suggest a commit message.

---

## 38. Agent Workflow After Editing Code

After changes, the agent should report:

```text
Changed files:
- ...

What changed:
- ...

Validation:
- Build: pass/fail/not run
- Runtime: pass/fail/not run
- Hardware: pass/fail/not run

Documentation:
- README: updated/not needed
- CHANGELOG: updated/not needed
- docs/hidpp-notes.md: updated/not needed
- docs/device-support.md: updated/not needed

Suggested commit:
- ...
```

Missing validation must be stated clearly.

---

## 39. Prohibited Agent Behavior

The agent must not:

- Assume issue numbers.
- Assign definite meanings to unverified HID++ byte values.
- Put platform-specific code in shared core logic.
- Add hardware-modifying write commands prematurely.
- Leave temporary debug output in final code.
- Skip documentation updates.
- Skip changelog updates.
- Mix unrelated features in one branch.
- Treat build success as completion.
- Expose raw protocol details through public APIs.
- Invent release notes.
- Generate Turkish project artifacts unless explicitly requested.

---

## 40. Preferred Response Style for Agents

When planning, include:

- Issue/milestone status
- Architectural impact
- File-level change plan
- Validation plan
- Documentation plan

When implementing, include:

- What changed
- Why this design was chosen
- Cross-platform impact
- HID++ safety impact
- Remaining validation gaps

When reviewing code, evaluate:

- Correctness
- Safety
- Architecture
- Error handling
- Documentation
- Tests
- Hardware validation

---

## 41. v0.2.0-alpha Specific Guidance

During `v0.2.0-alpha`, prioritize:

1. Battery improvements
2. Firmware information
3. Serial number support
4. Capability discovery

Actual task order must still follow verified GitHub issue and project board priority.

For battery improvements, these states must only be mapped after packet behavior is validated:

- Charging
- Discharging
- Full
- Unknown

For firmware information, the main deliverables are:

- DEVICE_FW_VERSION feature discovery
- Raw packet documentation
- Safe parser
- FirmwareInfo model
- CLI output

For capability discovery, consider:

- Vendor-neutral DeviceCapability
- Supported feature enumeration
- Future UI/API compatibility

---

## 42. Documentation Templates

### HID++ Observation Template

```md
## Feature: <FEATURE_NAME>

Device:
- Model:
- Vendor ID:
- Product ID:
- Connection:
- Platform:

Feature:
- Feature ID:
- Feature Index:
- Function:

Raw Request:

```text
...
```

Raw Response:

```text
...
```

Parsed Fields:

```text
response[0] = ...
response[1] = ...
response[2] = unknown
```

Interpretation:
- ...

Validation Status:
- Experimental / Verified / Confirmed

Notes:
- ...
```

### Device Support Template

```md
| Device | Vendor ID | Product ID | Discovery | Name | Battery | Firmware | Serial | Capabilities |
| ------ | --------- | ---------- | --------- | ---- | ------- | -------- | ------ | ------------ |
| Logitech PRO 2 LIGHTSPEED | 046d | 40a8 | Yes | Yes | Partial | Planned | Planned | Planned |
```

### Completion Report Template

```md
## Completion Report

Issue:
Milestone:
Branch:

Implemented:
- ...

Validation:
- [ ] Build successful
- [ ] Runtime verified
- [ ] Hardware tested
- [ ] Error paths checked

Documentation:
- [ ] README.md
- [ ] CHANGELOG.md
- [ ] docs/device-support.md
- [ ] docs/hidpp-notes.md

Known limitations:
- ...

Suggested commit:

```text
feat(scope): message
```
```

---

## 43. GitHub CLI Examples

Verify issue:

```bash
gh issue view <issue-number>
```

List milestone issues:

```bash
gh issue list --milestone "v0.2.0-alpha"
```

Create issue:

```bash
gh issue create \
  --title "Read firmware information from HID++ devices" \
  --body "..." \
  --milestone "v0.2.0-alpha" \
  --label "type:feature,area:hidpp,priority:high"
```

Close issue only after Definition of Done:

```bash
gh issue close <issue-number> --comment "Completed and validated."
```

Prefer CLI commands over manual GitHub UI steps when possible.

---

## 44. Final Principle

PeripheralOS agents must always follow this principle:

```text
Observe first.
Validate before interpreting.
Abstract before exposing.
Document before completing.
Protect hardware before adding features.
Write project outputs in English by default.
```

Code alone is not enough.

Successful PeripheralOS development requires clean architecture, safe protocol handling, verified hardware behavior, clear public APIs, updated documentation, changelog discipline, and synchronized GitHub project management.
