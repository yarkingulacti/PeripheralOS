#include "peripheralos/hidpp/UnifiedBatteryReader.hpp"

namespace peripheralos::hidpp
{
    namespace
    {
        constexpr std::uint8_t LongReportId = 0x11;
        constexpr std::uint8_t VeryLongReportId = 0x12;
        constexpr std::uint8_t ErrorFeatureIndex = 0xff;

        constexpr std::uint8_t GetCapabilitiesFunctionId = 0x00;
        constexpr std::uint8_t GetStatusFunctionId = 0x10;
        constexpr std::uint8_t StatusNotificationFunctionId = 0x00;

        constexpr std::size_t FirstParameterIndex = 4;
        constexpr std::size_t CapabilityResponseSize = FirstParameterIndex + 2;
        constexpr std::size_t StatusResponseSize = FirstParameterIndex + 4;

        BatteryStatus mapUnifiedBatteryStatus(
            const std::uint8_t chargingStatus,
            const std::uint8_t /* externalPowerStatus */
        )
        {
            // Linux hid-logitech-hidpp and Solaar agree on the public states
            // represented by values 0x00 through 0x03. Value 0x04 has
            // conflicting meanings between those references, so it and all
            // unrecognized values remain Unknown.
            switch (chargingStatus)
            {
            case 0x00:
                return BatteryStatus::Discharging;
            case 0x01:
            case 0x02:
                return BatteryStatus::Recharging;
            case 0x03:
                return BatteryStatus::Full;
            default:
                return BatteryStatus::Unknown;
            }
        }
    }

    UnifiedBatteryReader::UnifiedBatteryReader(
        const std::uint8_t featureIndex,
        const std::uint8_t deviceIndex
    )
        : featureIndex_(featureIndex), deviceIndex_(deviceIndex)
    {
    }

    bool UnifiedBatteryReader::updateCapabilities(const std::vector<std::uint8_t>& response)
    {
        if (!validatePacket(response, GetCapabilitiesFunctionId, CapabilityResponseSize))
        {
            return false;
        }

        supportedLevelFlags_ = response[FirstParameterIndex];
        capabilityFlags_ = response[FirstParameterIndex + 1];
        hasCapabilities_ = true;
        return true;
    }

    bool UnifiedBatteryReader::updateStatus(const std::vector<std::uint8_t>& response)
    {
        if (!hasCapabilities_ ||
            !validatePacket(response, GetStatusFunctionId, StatusResponseSize))
        {
            return false;
        }

        return updateBatteryState(response, true);
    }

    bool UnifiedBatteryReader::updateNotification(
        const std::vector<std::uint8_t>& notification
    )
    {
        if (!hasCapabilities_ ||
            !validatePacket(notification, StatusNotificationFunctionId, StatusResponseSize))
        {
            return false;
        }

        // Live fn=0x10 responses remain the authoritative percentage source.
        return updateBatteryState(notification, false);
    }

    std::optional<BatteryInfo> UnifiedBatteryReader::getBatteryInfo() const
    {
        if (!hasBatteryInfo_)
        {
            return std::nullopt;
        }

        return batteryInfo_;
    }

    bool UnifiedBatteryReader::validatePacket(
        const std::vector<std::uint8_t>& packet,
        const std::uint8_t functionId,
        const std::size_t minimumSize
    ) const
    {
        if (packet.size() < minimumSize)
        {
            return false;
        }

        if (packet[0] != LongReportId && packet[0] != VeryLongReportId)
        {
            return false;
        }

        if (packet[1] != deviceIndex_ || packet[2] == ErrorFeatureIndex)
        {
            return false;
        }

        if (packet[2] != featureIndex_)
        {
            return false;
        }

        return (packet[3] & 0xf0) == functionId;
    }

    bool UnifiedBatteryReader::updateBatteryState(
        const std::vector<std::uint8_t>& packet,
        const bool updatePercentage
    )
    {
        const auto stateOfCharge = packet[FirstParameterIndex];

        if (stateOfCharge > 100)
        {
            return false;
        }

        rawBatteryState_ = RawBatteryState{
            .levelFlags = packet[FirstParameterIndex + 1],
            .chargingStatus = packet[FirstParameterIndex + 2],
            .externalPowerStatus = packet[FirstParameterIndex + 3]
        };

        if (updatePercentage)
        {
            batteryInfo_.percentage = static_cast<int>(stateOfCharge);
            hasBatteryInfo_ = true;
        }

        batteryInfo_.status = mapUnifiedBatteryStatus(
            rawBatteryState_.chargingStatus,
            rawBatteryState_.externalPowerStatus
        );

        return true;
    }
}
