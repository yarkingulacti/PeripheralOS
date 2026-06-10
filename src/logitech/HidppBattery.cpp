#include "peripheralos/logitech/HidppBattery.hpp"

namespace peripheralos::logitech
{
    namespace
    {
        HidppBatteryStatus parseBatteryStatus(std::uint8_t statusByte)
        {
            switch (statusByte)
            {
            case 0x00:
                return HidppBatteryStatus::Discharging;
            case 0x01:
                return HidppBatteryStatus::Recharging;
            case 0x02:
                return HidppBatteryStatus::Full;
            case 0x03:
                return HidppBatteryStatus::Low;
            case 0x04:
                return HidppBatteryStatus::Critical;
            default:
                return HidppBatteryStatus::Unknown;
            }
        }
    }

    std::optional<HidppBatteryData> parseUnifiedBatteryResponse(
        const std::vector<std::uint8_t>& response
    )
    {
        if (response.size() < 7)
        {
            return std::nullopt;
        }

        const auto percentage = response[4];
        const auto statusByte = response[6];

        if (percentage > 100)
        {
            return std::nullopt;
        }

        return HidppBatteryData{
            .percentage = percentage,
            .statusByte = statusByte,
            .status = parseBatteryStatus(statusByte)
        };
    }

    std::string toString(HidppBatteryStatus status)
    {
        switch (status)
        {
        case HidppBatteryStatus::Discharging:
            return "discharging";
        case HidppBatteryStatus::Recharging:
            return "recharging";
        case HidppBatteryStatus::Full:
            return "full";
        case HidppBatteryStatus::Low:
            return "low";
        case HidppBatteryStatus::Critical:
            return "critical";
        case HidppBatteryStatus::Unknown:
        default:
            return "unknown";
        }
    }
}
