#include <fmt/core.h>

#include <exception>
#include <string>

#if PERIPHERALOS_PLATFORM_LINUX
#include "peripheralos/devices/DeviceIdentity.hpp"
#include "peripheralos/logitech/Hidpp20Client.hpp"
#include "peripheralos/platform/linux/LinuxHidDevice.hpp"
#include "peripheralos/platform/linux/LinuxHidDiscovery.hpp"
#endif

#ifndef PERIPHERALOS_VERSION_FULL
#define PERIPHERALOS_VERSION_FULL PERIPHERALOS_VERSION
#endif

#ifndef PERIPHERALOS_GIT_COMMIT
#define PERIPHERALOS_GIT_COMMIT "unknown"
#endif

namespace
{
    void printHeader()
    {
        fmt::print("\n");
        fmt::print("============================================================\n");
        fmt::print("  {} {}\n", PERIPHERALOS_NAME, PERIPHERALOS_VERSION_FULL);
        fmt::print("============================================================\n");
        fmt::print("  Platform : {}\n", PERIPHERALOS_PLATFORM);
        fmt::print("  Commit   : {}\n", PERIPHERALOS_GIT_COMMIT);
        fmt::print("  License  : {}\n", PERIPHERALOS_LICENSE);
        fmt::print("  Author   : {}\n", PERIPHERALOS_AUTHOR);
        fmt::print("============================================================\n\n");
    }

    void printFeatureStatus()
    {
        fmt::print("Runtime features:\n");
        fmt::print("  HID support      : {}\n", PERIPHERALOS_ENABLE_HID ? "enabled" : "disabled");
        fmt::print("  RGB support      : {}\n", PERIPHERALOS_ENABLE_RGB ? "enabled" : "disabled");
        fmt::print("  Profile support  : {}\n", PERIPHERALOS_ENABLE_PROFILES ? "enabled" : "disabled");
        fmt::print("\n");
    }

#if PERIPHERALOS_PLATFORM_LINUX

    void runLinuxHidDiscovery()
    {
        peripheralos::platform::linux::LinuxHidDiscovery discovery;
        const auto devices = discovery.discover();

        fmt::print("Linux HID discovery:\n");
        fmt::print("  Found {} HID device(s).\n\n", devices.size());

        for (const auto& device : devices)
        {
            const auto identity = peripheralos::devices::identifyDevice(
                device.vendorId,
                device.productId,
                device.name
            );

            fmt::print(
                "- {} | bus={} | {:04x}:{:04x} | {} | supported={}\n",
                device.path,
                device.busType,
                device.vendorId,
                device.productId,
                identity.displayName,
                identity.supported ? "yes" : "no"
            );

            if (!identity.supported)
            {
                continue;
            }

            peripheralos::platform::linux::LinuxHidDevice hidDevice(device.path);

            if (!hidDevice.open())
            {
                fmt::print("  -> failed to open. Check hidraw permissions or try udev rules.\n");
                continue;
            }

            fmt::print("  -> opened successfully\n");

            peripheralos::logitech::Hidpp20Client hidpp(hidDevice);

            const auto deviceNameFeatureIndex = hidpp.getFeatureIndex(0x0005);

            if (deviceNameFeatureIndex.has_value())
            {
                fmt::print("  -> HID++ DEVICE_NAME feature index: {}\n", *deviceNameFeatureIndex);
            }
            else
            {
                fmt::print("  -> HID++ DEVICE_NAME feature discovery failed\n");
            }

            const auto hidppNameLength = hidpp.getDeviceNameLength();

            if (hidppNameLength.has_value())
            {
                fmt::print("  -> HID++ device name length: {}\n", *hidppNameLength);
            }
            else
            {
                fmt::print("  -> HID++ device name length read failed\n");
            }

            const auto hidppName = hidpp.getDeviceName();

            if (hidppName.has_value())
            {
                fmt::print("  -> HID++ device name: {}\n", *hidppName);
            }
            else
            {
                fmt::print("  -> HID++ device name read failed\n");
            }
        }

        fmt::print("\n");
    }

#else

    void runUnsupportedPlatformNotice()
    {
        fmt::print("PeripheralOS CLI built successfully for this platform.\n\n");
        fmt::print("Current v0.1.0-alpha runtime support:\n");
        fmt::print("  Linux HID discovery       : available\n");
        fmt::print("  Logitech HID++ prototype  : available on Linux\n");
        fmt::print("  Windows backend           : planned\n");
        fmt::print("  macOS backend             : planned\n\n");
        fmt::print("This binary verifies that the cross-platform build pipeline works.\n");
    }

#endif
}

int main()
{
    try
    {
        printHeader();
        printFeatureStatus();

#if PERIPHERALOS_PLATFORM_LINUX
        runLinuxHidDiscovery();
#else
        runUnsupportedPlatformNotice();
#endif

        fmt::print("Done.\n");
        return 0;
    }
    catch (const std::exception& error)
    {
        fmt::print(stderr, "Fatal error: {}\n", error.what());
        return 1;
    }
}
