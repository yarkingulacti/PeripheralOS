#pragma once

#include "peripheralos/devices/BatteryInfo.hpp"

#include <cstdint>
#include <optional>
#include <vector>

namespace peripheralos::hidpp
{
    class UnifiedBatteryReader
    {
    public:
        explicit UnifiedBatteryReader(
            std::uint8_t featureIndex,
            std::uint8_t deviceIndex = 0x01
        );

        bool updateCapabilities(const std::vector<std::uint8_t>& response);
        bool updateStatus(const std::vector<std::uint8_t>& response);
        bool updateNotification(const std::vector<std::uint8_t>& notification);

        [[nodiscard]] std::optional<BatteryInfo> getBatteryInfo() const;

    private:
        struct RawBatteryState
        {
            std::uint8_t levelFlags = 0;
            std::uint8_t chargingStatus = 0;
            std::uint8_t externalPowerStatus = 0;
        };

        bool validatePacket(
            const std::vector<std::uint8_t>& packet,
            std::uint8_t functionId,
            std::size_t minimumSize
        ) const;
        bool updateBatteryState(
            const std::vector<std::uint8_t>& packet,
            bool updatePercentage
        );

        std::uint8_t featureIndex_;
        std::uint8_t deviceIndex_;
        std::uint8_t supportedLevelFlags_ = 0;
        std::uint8_t capabilityFlags_ = 0;
        RawBatteryState rawBatteryState_;
        BatteryInfo batteryInfo_;
        bool hasCapabilities_ = false;
        bool hasBatteryInfo_ = false;
    };
}
