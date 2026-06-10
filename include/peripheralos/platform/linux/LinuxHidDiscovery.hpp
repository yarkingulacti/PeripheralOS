#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace peripheralos::platform::linux
{
    struct HidDeviceInfo
    {
        std::string path;
        std::string name;
        std::string physicalPath;
        std::uint16_t vendorId{};
        std::uint16_t productId{};
        std::uint32_t busType{};
    };

    class LinuxHidDiscovery
    {
    public:
        std::vector<HidDeviceInfo> discover() const;
    };
}
