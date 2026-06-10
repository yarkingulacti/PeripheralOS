#pragma once

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
    };

    inline std::string toString(BatteryStatus status)
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
} // namespace peripheralos
