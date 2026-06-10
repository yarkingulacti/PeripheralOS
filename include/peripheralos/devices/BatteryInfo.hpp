#pragma once

#include <cstdint>
#include <string>

namespace peripheralos::devices
{
    enum class BatteryStatus
    {
        Unknown
    };

    struct BatteryInfo
    {
        std::uint8_t percentage{};
        BatteryStatus status{BatteryStatus::Unknown};
    };

    inline std::string toString(BatteryStatus status)
    {
        switch (status)
        {
        case BatteryStatus::Unknown:
        default:
            return "unknown";
        }
    }
}
