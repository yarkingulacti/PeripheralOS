#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace peripheralos::platform::linux
{
    class LinuxHidDevice
    {
    public:
        explicit LinuxHidDevice(std::string path);
        ~LinuxHidDevice();

        LinuxHidDevice(const LinuxHidDevice&) = delete;
        LinuxHidDevice& operator=(const LinuxHidDevice&) = delete;

        LinuxHidDevice(LinuxHidDevice&& other) noexcept;
        LinuxHidDevice& operator=(LinuxHidDevice&& other) noexcept;

        bool open();
        void close();

        [[nodiscard]] bool isOpen() const;
        [[nodiscard]] const std::string& path() const;
        [[nodiscard]] int fd() const;

        bool writeBytes(const std::vector<std::uint8_t>& bytes) const;
        std::vector<std::uint8_t> readBytes(std::size_t maxBytes) const;

    private:
        std::string path_;
        int fd_{-1};
    };
}
