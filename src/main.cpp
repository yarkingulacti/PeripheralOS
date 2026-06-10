#include "peripheralos/logitech/Hidpp20Client.hpp"
#include "peripheralos/platform/linux/LinuxHidDevice.hpp"
#include "peripheralos/devices/DeviceIdentity.hpp"
#include "peripheralos/platform/linux/LinuxHidDiscovery.hpp"

#include <fmt/core.h>

#include <exception>

int main()
{
    try
    {
        fmt::print("{} v{}\n", PERIPHERALOS_NAME, PERIPHERALOS_VERSION);
        fmt::print("Platform: {}\n\n", PERIPHERALOS_PLATFORM);

#if PERIPHERALOS_PLATFORM_LINUX
        peripheralos::platform::linux::LinuxHidDiscovery discovery;
        const auto devices = discovery.discover();

        fmt::print("HID devices:\n");

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

            if (identity.supported)
            {
                peripheralos::platform::linux::LinuxHidDevice hidDevice(device.path);

                if (hidDevice.open())
                {
                    fmt::print("  -> opened successfully\n");

                    peripheralos::logitech::Hidpp20Client hidpp(hidDevice);

                    const auto deviceNameFeatureIndex = hidpp.getFeatureIndex(0x0005);

                    if (deviceNameFeatureIndex.has_value())
                    {
                        fmt::print(
                            "  -> HID++ DEVICE_NAME feature index: {}\n",
                            *deviceNameFeatureIndex
                        );

                        const auto hidppNameLength = hidpp.getDeviceNameLength();

                        if (hidppNameLength.has_value())
                        {
                            fmt::print("  -> HID++ device name length: {}\n", *hidppNameLength);
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
                    else
                    {
                        fmt::print("  -> HID++ request failed\n");
                    }
                }
                else
                {
                    fmt::print("  -> failed to open. Try running with sudo or add udev rule.\n");
                }
            }
        }
#else
        fmt::print("HID discovery is not implemented for this platform yet.\n");
#endif

        return 0;
    }
    catch (const std::exception& error)
    {
        fmt::print(stderr, "Error: {}\n", error.what());
        return 1;
    }
}
