#include "peripheralos/logitech/Hidpp20Client.hpp"
#include "peripheralos/logitech/Hidpp20FeatureIds.hpp"
#include "peripheralos/logitech/HidppBattery.hpp"

#include <chrono>
#include <thread>

namespace peripheralos::logitech
{
    namespace
    {
        constexpr std::uint8_t ShortReportId = 0x10;
        constexpr std::uint8_t DeviceIndex = 0x01;
        constexpr std::uint8_t SoftwareId = 0x01;

        constexpr std::size_t ShortReportSize = 7;
    }

    Hidpp20Client::Hidpp20Client(platform::linux::LinuxHidDevice& device)
        : device_(device)
    {
    }

    std::vector<std::uint8_t> Hidpp20Client::request(
        std::uint8_t featureIndex,
        std::uint8_t functionId,
        const std::vector<std::uint8_t>& params
    )
    {
        // Drain old input reports
        while (true)
        {
            auto old = device_.readBytes(64);
            if (old.empty())
            {
                break;
            }
        }

        std::vector<std::uint8_t> packet(ShortReportSize, 0x00);

        packet[0] = ShortReportId; // 0x10
        packet[1] = DeviceIndex; // 0x01
        packet[2] = featureIndex;
        packet[3] = static_cast<std::uint8_t>((functionId << 4) | SoftwareId);

        for (std::size_t i = 0; i < params.size() && i < 3; ++i)
        {
            packet[4 + i] = params[i];
        }

        if (!device_.writeBytes(packet))
        {
            return {};
        }

        for (int attempt = 0; attempt < 50; ++attempt)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            auto response = device_.readBytes(64);

            if (response.empty())
            {
                continue;
            }

            // Ignore normal mouse/input reports.
            if (response[0] != 0x10 && response[0] != 0x11)
            {
                continue;
            }

            // Must be our paired device.
            if (response.size() > 1 && response[1] != DeviceIndex)
            {
                continue;
            }

            // HID++ error response.
            if (response.size() > 2 && response[2] == 0xff)
            {
                return response;
            }

            // Must match requested feature index.
            if (response.size() > 2 && response[2] != featureIndex)
            {
                continue;
            }

            return response;
        }

        return {};
    }

    std::optional<std::uint8_t> Hidpp20Client::getFeatureIndex(std::uint16_t featureId)
    {
        const auto response = request(
            0x00,
            0x00,
            {
                static_cast<std::uint8_t>((featureId >> 8) & 0xff),
                static_cast<std::uint8_t>(featureId & 0xff),
                0x00
            }
        );

        if (response.size() < 7)
        {
            return std::nullopt;
        }

        if (response[2] == 0xff)
        {
            return std::nullopt;
        }

        return response[4];
    }

    std::optional<std::uint8_t> Hidpp20Client::getDeviceNameLength()
    {
        const auto featureIndex = getFeatureIndex(hidpp20::features::DeviceName);

        if (!featureIndex.has_value())
        {
            return std::nullopt;
        }

        const auto response = request(
            *featureIndex,
            0x00,
            {0x00, 0x00, 0x00}
        );

        if (response.size() < 5 || response[2] == 0xff)
        {
            return std::nullopt;
        }

        return response[4];
    }

    std::optional<std::string> Hidpp20Client::getDeviceName()
    {
        const auto featureIndex = getFeatureIndex(hidpp20::features::DeviceName);

        if (!featureIndex.has_value())
        {
            return std::nullopt;
        }

        const auto nameLength = getDeviceNameLength();

        if (!nameLength.has_value() || *nameLength == 0)
        {
            return std::nullopt;
        }

        std::string name;
        std::uint8_t offset = 0;

        while (name.size() < *nameLength)
        {
            const auto response = request(
                *featureIndex,
                0x01,
                {offset, 0x00, 0x00}
            );

            if (response.size() < 5 || response[2] == 0xff)
            {
                return std::nullopt;
            }

            for (std::size_t i = 4; i < response.size() && name.size() < *nameLength; ++i)
            {
                if (response[i] == 0x00)
                {
                    break;
                }

                name.push_back(static_cast<char>(response[i]));
            }

            if (response.size() <= 4)
            {
                break;
            }

            offset = static_cast<std::uint8_t>(name.size());
        }

        if (name.empty())
        {
            return std::nullopt;
        }

        return name;
    }

    std::vector<std::uint8_t> Hidpp20Client::debugRequest(
        std::uint8_t featureIndex,
        std::uint8_t functionId,
        const std::vector<std::uint8_t>& params
    )
    {
        return request(featureIndex, functionId, params);
    }

    std::optional<BatteryInfo> Hidpp20Client::getBatteryInfo()
    {
        const auto featureIndex = getFeatureIndex(hidpp20::features::UnifiedBattery);

        if (!featureIndex.has_value())
        {
            return std::nullopt;
        }

        const auto response = request(
            *featureIndex,
            0x00,
            {0x00, 0x00, 0x00}
        );

        const auto parsedBattery = parseUnifiedBatteryResponse(response);

        if (!parsedBattery.has_value())
        {
            return std::nullopt;
        }

        return BatteryInfo{
            .percentage = parsedBattery->percentage,
            .status = mapUnifiedBatteryStatus(parsedBattery->statusByte),
            .rawLevel = parsedBattery->level,
            .rawStatusByte = parsedBattery->statusByte
        };
    }

    std::vector<std::uint16_t> Hidpp20Client::enumerateFeatures()
    {
        std::vector<std::uint16_t> features;

        const auto featureSetIndex =
            getFeatureIndex(hidpp20::features::FeatureSet);

        if (!featureSetIndex.has_value())
        {
            return features;
        }

        const auto countResponse = request(
            *featureSetIndex,
            0x00,
            {0x00, 0x00, 0x00}
        );

        if (countResponse.size() < 5 || countResponse[2] == 0xff)
        {
            return features;
        }

        const auto featureCount = countResponse[4];

        for (std::uint8_t featureNumber = 0; featureNumber < featureCount; ++featureNumber)
        {
            const auto response = request(
                *featureSetIndex,
                0x01,
                {featureNumber, 0x00, 0x00}
            );

            if (response.size() < 6 || response[2] == 0xff)
            {
                continue;
            }

            const auto featureId =
                static_cast<std::uint16_t>(
                    (static_cast<std::uint16_t>(response[4]) << 8) |
                    response[5]
                );

            features.push_back(featureId);
        }

        return features;
    }
}
