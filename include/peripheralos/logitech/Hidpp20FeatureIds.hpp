#pragma once

#include <cstdint>

namespace peripheralos::logitech::hidpp20::features
{
    constexpr std::uint16_t FeatureSet = 0x0001;
    constexpr std::uint16_t DeviceName = 0x0005;
    constexpr std::uint16_t UnifiedBattery = 0x1004;
}
