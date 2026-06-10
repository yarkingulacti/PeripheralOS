#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace peripheralos::logitech
{
    enum class HidppBatteryStatus
    {
        Unknown,
        Discharging,
        Recharging,
        Full,
        Low,
        Critical
    };

    struct HidppBatteryData
    {
        std::uint8_t percentage{};
        std::uint8_t statusByte{};
        HidppBatteryStatus status{HidppBatteryStatus::Unknown};
    };

    std::optional<HidppBatteryData> parseUnifiedBatteryResponse(
        const std::vector<std::uint8_t>& response
    );

    std::string toString(HidppBatteryStatus status);
}
