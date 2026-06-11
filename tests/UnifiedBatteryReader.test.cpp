#include "peripheralos/hidpp/UnifiedBatteryReader.hpp"

#include <doctest/doctest.h>

#include <cstdint>
#include <vector>

namespace
{
    constexpr std::uint8_t FeatureIndex = 0x07;

    std::vector<std::uint8_t> capabilitiesResponse()
    {
        return {0x11, 0x01, FeatureIndex, 0x01, 0x0f, 0x03};
    }

    std::vector<std::uint8_t> statusResponse()
    {
        return {0x11, 0x01, FeatureIndex, 0x11, 31, 0x04, 0x01, 0x01};
    }
}

TEST_CASE("Unified battery maps charging status")
{
    peripheralos::hidpp::UnifiedBatteryReader reader(FeatureIndex);

    REQUIRE(reader.updateCapabilities(capabilitiesResponse()));
    REQUIRE(reader.updateStatus(statusResponse()));

    const auto batteryInfo = reader.getBatteryInfo();
    REQUIRE(batteryInfo.has_value());
    CHECK(batteryInfo->percentage == 31);
    CHECK(batteryInfo->status == peripheralos::BatteryStatus::Recharging);
}

TEST_CASE("Unified battery maps validated discharging status")
{
    peripheralos::hidpp::UnifiedBatteryReader reader(FeatureIndex);
    REQUIRE(reader.updateCapabilities(capabilitiesResponse()));

    auto dischargingResponse = statusResponse();
    dischargingResponse[6] = 0x00;
    REQUIRE(reader.updateStatus(dischargingResponse));

    const auto batteryInfo = reader.getBatteryInfo();
    REQUIRE(batteryInfo.has_value());
    CHECK(batteryInfo->status == peripheralos::BatteryStatus::Discharging);
}

TEST_CASE("Unified battery maps slow charging and full statuses")
{
    peripheralos::hidpp::UnifiedBatteryReader reader(FeatureIndex);
    REQUIRE(reader.updateCapabilities(capabilitiesResponse()));

    auto slowChargingResponse = statusResponse();
    slowChargingResponse[6] = 0x02;
    REQUIRE(reader.updateStatus(slowChargingResponse));
    REQUIRE(reader.getBatteryInfo().has_value());
    CHECK(reader.getBatteryInfo()->status == peripheralos::BatteryStatus::Recharging);

    auto fullResponse = statusResponse();
    fullResponse[6] = 0x03;
    REQUIRE(reader.updateStatus(fullResponse));
    REQUIRE(reader.getBatteryInfo().has_value());
    CHECK(reader.getBatteryInfo()->status == peripheralos::BatteryStatus::Full);
}

TEST_CASE("Unified battery keeps conflicting and unknown statuses unknown")
{
    peripheralos::hidpp::UnifiedBatteryReader reader(FeatureIndex);
    REQUIRE(reader.updateCapabilities(capabilitiesResponse()));

    auto conflictingResponse = statusResponse();
    conflictingResponse[6] = 0x04;
    REQUIRE(reader.updateStatus(conflictingResponse));
    REQUIRE(reader.getBatteryInfo().has_value());
    CHECK(reader.getBatteryInfo()->status == peripheralos::BatteryStatus::Unknown);

    auto unknownResponse = statusResponse();
    unknownResponse[6] = 0xff;
    REQUIRE(reader.updateStatus(unknownResponse));
    REQUIRE(reader.getBatteryInfo().has_value());
    CHECK(reader.getBatteryInfo()->status == peripheralos::BatteryStatus::Unknown);
}

TEST_CASE("Unified battery capabilities do not produce battery information")
{
    peripheralos::hidpp::UnifiedBatteryReader reader(FeatureIndex);

    REQUIRE(reader.updateCapabilities(capabilitiesResponse()));
    CHECK_FALSE(reader.getBatteryInfo().has_value());
}

TEST_CASE("Unified battery parser rejects malformed and unexpected packets")
{
    peripheralos::hidpp::UnifiedBatteryReader reader(FeatureIndex);
    REQUIRE(reader.updateCapabilities(capabilitiesResponse()));

    auto shortResponse = statusResponse();
    shortResponse.resize(7);
    CHECK_FALSE(reader.updateStatus(shortResponse));

    auto errorResponse = statusResponse();
    errorResponse[2] = 0xff;
    CHECK_FALSE(reader.updateStatus(errorResponse));

    auto wrongFunctionResponse = statusResponse();
    wrongFunctionResponse[3] = 0x21;
    CHECK_FALSE(reader.updateStatus(wrongFunctionResponse));

    auto invalidPercentageResponse = statusResponse();
    invalidPercentageResponse[4] = 101;
    CHECK_FALSE(reader.updateStatus(invalidPercentageResponse));

    auto wrongReportResponse = statusResponse();
    wrongReportResponse[0] = 0x10;
    CHECK_FALSE(reader.updateStatus(wrongReportResponse));

    auto wrongDeviceResponse = statusResponse();
    wrongDeviceResponse[1] = 0x02;
    CHECK_FALSE(reader.updateStatus(wrongDeviceResponse));

    auto wrongFeatureResponse = statusResponse();
    wrongFeatureResponse[2] = 0x08;
    CHECK_FALSE(reader.updateStatus(wrongFeatureResponse));
}

TEST_CASE("Unified battery notification does not replace live percentage")
{
    peripheralos::hidpp::UnifiedBatteryReader reader(FeatureIndex);
    REQUIRE(reader.updateCapabilities(capabilitiesResponse()));
    REQUIRE(reader.updateStatus(statusResponse()));

    auto notification = statusResponse();
    notification[3] = 0x00;
    notification[4] = 45;
    notification[6] = 0x03;

    REQUIRE(reader.updateNotification(notification));

    const auto batteryInfo = reader.getBatteryInfo();
    REQUIRE(batteryInfo.has_value());
    CHECK(batteryInfo->percentage == 31);
    CHECK(batteryInfo->status == peripheralos::BatteryStatus::Full);
}
