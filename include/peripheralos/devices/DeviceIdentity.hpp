#pragma once

#include <cstdint>
#include <string>

namespace peripheralos::devices
{
    enum class DeviceVendor
    {
        Unknown,
        Logitech,
        Wraith,
    };

    enum class DeviceKind
    {
        Unknown,
        Mouse,
        Keyboard,
        Headset,
        Receiver,
    };

    struct DeviceIdentity
    {
        DeviceVendor vendor{DeviceVendor::Unknown};
        DeviceKind kind{DeviceKind::Unknown};
        std::string displayName;
        std::string codename;
        bool supported{false};
    };

    DeviceIdentity identifyDevice(
        std::uint16_t vendorId,
        std::uint16_t productId,
        const std::string& name
    );
}
