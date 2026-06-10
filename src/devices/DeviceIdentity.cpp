#include "peripheralos/devices/DeviceIdentity.hpp"

namespace peripheralos::devices
{
    DeviceIdentity identifyDevice(
        std::uint16_t vendorId,
        std::uint16_t productId,
        const std::string& name
    )
    {
        if (vendorId == 0x046d && productId == 0x40a8)
        {
            return {
                DeviceVendor::Logitech,
                DeviceKind::Mouse,
                "Logitech PRO 2 LIGHTSPEED",
                "logitech-pro-2-lightspeed",
                true
            };
        }

        if (vendorId == 0x046d && productId == 0xc543)
        {
            return {
                DeviceVendor::Logitech,
                DeviceKind::Receiver,
                "Logitech LIGHTSPEED Receiver",
                "logitech-lightspeed-receiver",
                false
            };
        }

        if (vendorId == 0x046d && productId == 0x0aba)
        {
            return {
                DeviceVendor::Logitech,
                DeviceKind::Headset,
                "Logitech PRO X Wireless Gaming Headset",
                "logitech-pro-x-wireless-headset",
                false
            };
        }

        if (vendorId == 0x2e3c && productId == 0xc365)
        {
            return {
                DeviceVendor::Wraith,
                DeviceKind::Keyboard,
                "Wraith W75",
                "wraith-w75",
                false
            };
        }

        return {
            DeviceVendor::Unknown,
            DeviceKind::Unknown,
            name.empty() ? "Unknown HID Device" : name,
            "unknown",
            false
        };
    }
}
