# Architecture

PeripheralOS is divided into four major layers.

## UI Layer

Qt based graphical interface.

## Daemon Layer

Background service responsible for:

* Device discovery
* Profile management
* Macro execution
* RGB synchronization

## Core Layer

Business logic.

## Hardware Layer

Platform specific integrations.

### Linux

* hidraw
* libudev

### Windows

* RawInput
* SetupAPI
* HIDAPI

### macOS

* IOKit
