#pragma once

#include <cstdint>
#include <optional>
#include <vector>

namespace peripheralos::logitech
{
    struct HidppBatteryData
    {
        int percentage = -1;
        std::uint8_t level = 0;
        std::uint8_t statusByte = 0;
    };

    std::optional<HidppBatteryData> parseUnifiedBatteryResponse(
        const std::vector<std::uint8_t>& response
    );
}
