# Security Policy

## Supported Versions

| Version      | Supported |
|--------------|-----------|
| v0.2.x-alpha | ✅         |
| v0.1.x-alpha | ❌         |

Only the latest development milestone receives security-related fixes.

---

## Reporting a Vulnerability

If you discover a security vulnerability, please do not open a public issue immediately.

Instead:

1. Contact the maintainer privately.
2. Provide detailed reproduction steps.
3. Include affected versions.
4. Include proof-of-concept information when appropriate.

---

## Scope

Examples of relevant vulnerabilities:

* Arbitrary code execution
* Privilege escalation
* Unsafe device access
* Memory corruption
* Remote attack vectors
* Sensitive information exposure

Examples of non-security issues:

* Feature requests
* Device compatibility requests
* Documentation issues
* General bugs

---

## Disclosure Process

1. Vulnerability reported.
2. Investigation performed.
3. Fix developed.
4. Fix released.
5. Public disclosure when appropriate.

---

## Device Safety

PeripheralOS interacts directly with hardware devices.

Security and safety are treated as equally important.

The project prioritizes:

* Read-only implementation before write support
* Protocol validation
* Hardware safety
* Defensive programming

See docs/design-principles.md for additional details.
