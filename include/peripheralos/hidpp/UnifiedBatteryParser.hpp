#pragma once

#include "peripheralos/devices/BatteryInfo.hpp"

#include <cstdint>
#include <optional>
#include <vector>

namespace peripheralos::hidpp
{
    std::optional<BatteryInfo> parseUnifiedBatteryResponse(
        const std::vector<std::uint8_t>& response
    );
}
