#include "peripheralos/hidpp/UnifiedBatteryParser.hpp"

namespace peripheralos::hidpp
{
    std::optional<BatteryInfo> parseUnifiedBatteryResponse(
        const std::vector<std::uint8_t>& response
    )
    {
        if (response.size() < 7)
        {
            return std::nullopt;
        }

        const auto percentage = static_cast<int>(response[4]);
        [[maybe_unused]] const auto statusByte = response[6];

        return BatteryInfo{
            .percentage = percentage,
            .status = BatteryStatus::Unknown
        };
    }
}
