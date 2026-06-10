#pragma once

#include <cstdint>
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

        std::uint8_t rawLevel = 0;
        std::uint8_t rawStatusByte = 0;
    };

    inline std::string toString(const BatteryStatus status)
    {
        switch (status)
        {
        case BatteryStatus::Recharging:
            return "recharging";
        case BatteryStatus::Full:
            return "full";
        case BatteryStatus::Discharging:
            return "discharging";
        case BatteryStatus::Unknown:
        default:
            return "unknown";
        }
    }

    inline BatteryStatus mapUnifiedBatteryStatus(const std::uint8_t /* statusByte */)
    {
        return BatteryStatus::Unknown;
    }
}
