#include "peripheralos/logitech/HidppBattery.hpp"

namespace peripheralos::logitech
{
    std::optional<HidppBatteryData> parseUnifiedBatteryResponse(
        const std::vector<std::uint8_t>& response
    )
    {
        if (response.size() < 7)
        {
            return std::nullopt;
        }

        return HidppBatteryData{
            .percentage = response[4],
            .statusByte = response[6]
        };
    }
}
