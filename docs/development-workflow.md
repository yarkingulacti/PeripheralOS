# Development Workflow

This document describes the standard development workflow used by PeripheralOS.

---

# Branch Strategy

PeripheralOS uses the following branch model:

```text
master
dev
feature/*
```

---

# Branch Purposes

## master

Production-ready branch.

Rules:

* Release-ready code only
* Tagged releases originate from this branch

---

## dev

Active development branch.

Rules:

* New features merge here first
* Integration testing happens here

---

## feature/*

Feature branches.

Examples:

```text
feature/hidpp-battery
feature/device-capabilities
feature/fw-version
```

Rules:

* One feature per branch
* Short-lived branches preferred

---

# Feature Development Process

## 1. Update Development Branch

```bash
git checkout dev
git pull origin dev
```

---

## 2. Create Feature Branch

```bash
git checkout -b feature/hidpp-battery
```

---

## 3. Implement Feature

Examples:

* Source code
* Tests
* Documentation

Required documentation updates:

* README.md
* CHANGELOG.md
* Relevant docs/

---

## 4. Commit Changes

Use Conventional Commits.

Examples:

```text
feat(hidpp): add unified battery support
feat(device): introduce capability model
fix(linux): filter invalid hid reports
docs(hidpp): document battery responses
```

---

## 5. Merge Into Development

```bash
git checkout dev
git merge feature/hidpp-battery
git push origin dev
```

---

## 6. Release Preparation

Before a release:

* Build succeeds
* Tests pass
* Documentation updated
* Changelog updated

---

## 7. Release Merge

```bash
git checkout master
git merge dev
git push origin master
```

---

## 8. Create Release Tag

Example:

```bash
git tag -a v0.2.0-alpha -m "PeripheralOS v0.2.0-alpha"
git push origin v0.2.0-alpha
```

---

# Pull Request Expectations

Every pull request should:

* Solve a single problem
* Include clear descriptions
* Follow project architecture
* Update documentation when necessary

---

# Documentation Rule

A feature is not complete until its documentation is updated.

Documentation changes are considered part of the implementation.

---

# Code Review Checklist

Before merging:

* Architecture respected
* Cross-platform implications considered
* No unnecessary complexity
* Documentation updated
* Build succeeds
* Tests pass

---

# Development Philosophy

PeripheralOS values:

* Maintainability
* Safety
* Clarity
* Documentation quality
* Long-term scalability

Short-term shortcuts should not compromise long-term architecture.
