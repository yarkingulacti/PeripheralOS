#pragma once

#include <cstdint>
#include <optional>
#include <vector>

namespace peripheralos::logitech
{
    struct HidppBatteryData
    {
        std::uint8_t percentage{};
        std::uint8_t statusByte{};
    };

    std::optional<HidppBatteryData> parseUnifiedBatteryResponse(
        const std::vector<std::uint8_t>& response
    );
}
