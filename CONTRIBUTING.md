# Release Process

PeripheralOS releases are created from Git tags.

Release version, release title, release artifacts and GitHub Releases are generated from the pushed version tag.

---

## Release Branch Policy

PeripheralOS uses the following branch model:

```text
master      -> release branch
dev         -> active development branch
feature/*   -> isolated feature branches
```

### Rules

* All development must happen in `dev` or `feature/*` branches.
* `master` must only contain release-ready code.
* Releases must always be created from `master`.
* Feature branches must be merged into `dev`.
* `dev` must be merged into `master` before creating a release tag.

---

## Versioning

PeripheralOS follows Semantic Versioning.

Examples:

```text
v0.1.0-alpha
v0.2.0-alpha
v0.3.0-beta
v1.0.0
```

### Release Types

| Type   | Description                      |
|--------|----------------------------------|
| alpha  | Early development release        |
| beta   | Feature-complete testing release |
| rc     | Release candidate                |
| stable | Production-ready release         |

---

## Release Workflow

### 1. Develop Features

Create a feature branch:

```bash
git checkout dev
git checkout -b feature/hidpp-battery
```

Work on the feature and commit changes.

---

### 2. Merge Into Development

```bash
git checkout dev
git merge feature/hidpp-battery
git push origin dev
```

---

### 3. Prepare Release

Verify the project builds successfully:

```bash
cmake -B build-release -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build-release
```

Update:

* CHANGELOG.md
* README.md (if required)
* Documentation

---

### 4. Merge Development Into Master

```bash
git checkout master
git merge dev
git push origin master
```

---

### 5. Create Release Tag

Example:

```bash
git tag -a v0.2.0-alpha -m "PeripheralOS v0.2.0-alpha"
git push origin v0.2.0-alpha
```

---

### 6. GitHub Actions Release

After pushing a version tag, GitHub Actions automatically:

* Builds Linux binaries
* Builds Windows binaries
* Builds macOS binaries
* Packages release artifacts
* Extracts release notes from `CHANGELOG.md`
* Creates a GitHub Release
* Marks alpha, beta and rc versions as pre-releases

No manual GitHub Release creation is required.

---

## Changelog Requirements

Every release must have a matching changelog entry.

Release notes are generated from `CHANGELOG.md`.

Required structure:

```md
## [0.2.0-alpha] - YYYY-MM-DD

### 🚀 Added

#### Core Infrastructure

- ...

#### Device Layer

- ...

#### Vendor Support

- ...

#### Runtime Improvements

- ...

---

### ✅ Supported Devices

#### Vendor

- Device

---

### ⚠ Known Limitations

#### Platform Support

- ...

#### Device Features

- ...

#### User Experience

- ...

---

### 📦 Release Artifacts

- Linux x86_64
- Windows x86_64
- macOS

---

### 📝 Notes

...

---

### 🎯 Next Milestone

#### v0.3.0-alpha

- ...
```

---

## Device Support Classification

Supported devices must be classified using one of the following levels:

### Detection Only

The device can be discovered but no functionality is implemented.

Example:

```text
Wraith W75 (detection only)
```

### Experimental

The device is partially supported and APIs may change.

Example:

```text
Logitech PRO 2 LIGHTSPEED (experimental)
```

### Functional

Core functionality is implemented and tested.

Example:

```text
Logitech PRO 2 LIGHTSPEED (functional)
```

### Stable

The device is considered production-ready.

Example:

```text
Logitech PRO 2 LIGHTSPEED (stable)
```

---

## Release Artifacts

Current release targets:

* Linux x86_64
* Windows x86_64
* macOS

Artifact naming convention:

```text
peripheralos-<version>-<platform>
```

Examples:

```text
peripheralos-v0.1.0-alpha-linux-x86_64.tar.gz
peripheralos-v0.1.0-alpha-windows-x86_64.zip
peripheralos-v0.1.0-alpha-macos-arm64.tar.gz
```

---

## Moving an Existing Tag

If a release tag was created before the final release commit:

```bash
git tag -d v0.1.0-alpha
git tag -a v0.1.0-alpha -m "PeripheralOS v0.1.0-alpha"
```

If the tag was already pushed:

```bash
git push origin :refs/tags/v0.1.0-alpha
git push origin v0.1.0-alpha
```

Use this carefully because moving published tags may confuse contributors.
