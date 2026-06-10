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

        if (response[2] == 0xff)
        {
            return std::nullopt;
        }

        return HidppBatteryData{
            .percentage = static_cast<int>(response[4]),
            .secondary = response[5],
            .statusByte = response[6]
        };
    }
}
