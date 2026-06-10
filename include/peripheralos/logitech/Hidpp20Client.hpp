#pragma once

#include "peripheralos/platform/linux/LinuxHidDevice.hpp"
#include "peripheralos/devices/BatteryInfo.hpp"

#include <cstdint>
#include <optional>
#include <vector>
#include <string>

namespace peripheralos::logitech
{
    class Hidpp20Client
    {
    public:
        explicit Hidpp20Client(platform::linux::LinuxHidDevice& device);

        std::optional<std::uint8_t> getFeatureIndex(std::uint16_t featureId);
        std::optional<std::uint8_t> getDeviceNameLength();
        std::optional<std::string> getDeviceName();
        std::vector<std::uint8_t> debugRequest(
            std::uint8_t featureIndex,
            std::uint8_t functionId,
            const std::vector<std::uint8_t>& params
        );
        std::optional<devices::BatteryInfo> getBatteryInfo();

    private:
        platform::linux::LinuxHidDevice& device_;

        std::vector<std::uint8_t> request(
            std::uint8_t featureIndex,
            std::uint8_t functionId,
            const std::vector<std::uint8_t>& params
        );
    };
}
