#include <fmt/core.h>

#include <exception>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstdint>

#if PERIPHERALOS_PLATFORM_LINUX
#include "peripheralos/devices/DeviceIdentity.hpp"
#include "peripheralos/logitech/Hidpp20Client.hpp"
#include "peripheralos/logitech/Hidpp20FeatureIds.hpp"
#include "peripheralos/logitech/HidppBattery.hpp"
#include "peripheralos/hidpp/UnifiedBatteryParser.hpp"
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
    std::string toHexString(const std::vector<std::uint8_t>& data)
    {
        std::ostringstream output;

        for (std::size_t i = 0; i < data.size(); ++i)
        {
            if (i > 0)
            {
                output << ' ';
            }

            output << std::uppercase
                << std::hex
                << std::setw(2)
                << std::setfill('0')
                << static_cast<int>(data[i]);
        }

        return output.str();
    }

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

            const auto deviceNameFeatureIndex =
                hidpp.getFeatureIndex(peripheralos::logitech::hidpp20::features::DeviceName);
            const auto unifiedBatteryFeatureIndex =
                hidpp.getFeatureIndex(peripheralos::logitech::hidpp20::features::UnifiedBattery);

            if (unifiedBatteryFeatureIndex.has_value())
            {
                fmt::print("  -> HID++ UNIFIED_BATTERY feature index: {}\n", *unifiedBatteryFeatureIndex);

                const auto batteryResponse =
                    hidpp.debugRequest(
                        *unifiedBatteryFeatureIndex,
                        0x00,
                        {0x00, 0x00, 0x00}
                    );

                if (!batteryResponse.empty())
                {
                    fmt::print(
                        "  -> Battery raw response: {}\n",
                        toHexString(batteryResponse)
                    );

                    const auto parsedBattery =
                        peripheralos::logitech::parseUnifiedBatteryResponse(
                            batteryResponse
                        );

                    if (parsedBattery.has_value())
                    {
                        fmt::print(
                            "  -> Battery: {}%, status=unknown\n",
                            parsedBattery->percentage
                        );

                        fmt::print(
                            "  -> Battery raw fields: percentage={}, secondary={}, statusByte={}\n",
                            parsedBattery->percentage,
                            parsedBattery->secondaryLevel,
                            parsedBattery->statusByte
                        );
                    }
                    else
                    {
                        fmt::print("  -> Battery info read failed\n");
                    }
                }
                else
                {
                    fmt::print("  -> UNIFIED_BATTERY request failed\n");
                }
            }
            else
            {
                fmt::print("  -> HID++ UNIFIED_BATTERY feature discovery failed\n");
            }


            if (deviceNameFeatureIndex.has_value())
            {
                fmt::print("  -> HID++ DEVICE_NAME feature index: {}\n", *deviceNameFeatureIndex);
            }
            else
            {
                fmt::print("  -> HID++ DEVICE_NAME feature discovery failed\n");
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
