# Contributing to PeripheralOS

Thank you for your interest in contributing to PeripheralOS.

PeripheralOS is an open-source cross-platform peripheral management platform focused on maintainability, safety and
long-term sustainability.

---

# Before Contributing

Please review:

* README.md
* docs/design-principles.md
* docs/architecture.md
* docs/project-structure.md
* docs/development-workflow.md

Understanding the project's architecture and philosophy helps keep contributions consistent.

---

# Development Requirements

## Languages

* C++20

## Build System

* CMake
* Ninja

## Platforms

* Linux
* Windows
* macOS

---

# Branch Strategy

PeripheralOS uses:

```text
master
dev
feature/*
```

### master

Production-ready branch.

### dev

Active development branch.

### feature/*

Feature-specific branches.

Example:

```text
feature/unified-battery
feature/device-capabilities
feature/fw-version
```

---

# Commit Convention

Use Conventional Commits.

Examples:

```text
feat(hidpp): add unified battery support
feat(device): add capability model
fix(linux): handle invalid hid reports
docs(roadmap): update v0.2.0-alpha goals
refactor(core): simplify device discovery
```

---

# Pull Requests

Every pull request should:

* Solve a single problem
* Follow project architecture
* Build successfully
* Update documentation when required

Checklist:

* [ ] Builds successfully
* [ ] Documentation updated
* [ ] CHANGELOG updated
* [ ] Architecture respected
* [ ] Tested locally

---

# Documentation Rule

Documentation is considered part of the implementation.

Relevant documentation must be updated whenever functionality changes.

Examples:

* README.md
* CHANGELOG.md
* docs/architecture.md
* docs/device-support.md
* docs/hidpp-notes.md
* docs/roadmap.md

---

# Code Style

Prefer:

* RAII
* std::unique_ptr
* std::optional
* Explicit ownership

Avoid:

* Raw owning pointers
* Global mutable state
* Hidden dependencies

---

# Reporting Issues

When reporting issues include:

* Platform
* Device
* Reproduction steps
* Logs
* Expected behavior
* Actual behavior

---

# Community

Be respectful and constructive.

See CODE_OF_CONDUCT.md for details.
