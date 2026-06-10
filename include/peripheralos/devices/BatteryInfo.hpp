#pragma once

#include <cstdint>
#include <string>

namespace peripheralos
{
    enum class BatteryStatus
    {
        Unknown,
        Charging,
        Discharging,
        Full
    };

    struct BatteryInfo
    {
        int percentage = -1;
        BatteryStatus status = BatteryStatus::Unknown;

        std::uint8_t rawSecondary = 0;
        std::uint8_t rawStatusByte = 0;
    };

    inline std::string toString(const BatteryStatus status)
    {
        switch (status)
        {
        case BatteryStatus::Charging:
            return "charging";
        case BatteryStatus::Discharging:
            return "discharging";
        case BatteryStatus::Full:
            return "full";
        case BatteryStatus::Unknown:
        default:
            return "unknown";
        }
    }
}
