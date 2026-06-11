#pragma once

#include <string>

namespace peripheralos
{
    enum class BatteryStatus
    {
        Unknown,
        Recharging,
        Full,
        Discharging
    };

    struct BatteryInfo
    {
        int percentage = -1;
        BatteryStatus status = BatteryStatus::Unknown;
    };

    inline std::string toString(const BatteryStatus status)
    {
        switch (status)
        {
        case BatteryStatus::Recharging:
            return "Charging";
        case BatteryStatus::Full:
            return "Full";
        case BatteryStatus::Discharging:
            return "Discharging";
        case BatteryStatus::Unknown:
        default:
            return "Unknown";
        }
    }
}
