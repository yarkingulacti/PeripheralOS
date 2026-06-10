#include "peripheralos/platform/linux/LinuxHidDevice.hpp"

#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <utility>
#include <vector>

namespace peripheralos::platform::linux
{
    LinuxHidDevice::LinuxHidDevice(std::string path)
        : path_(std::move(path))
    {
    }

    LinuxHidDevice::~LinuxHidDevice()
    {
        close();
    }

    LinuxHidDevice::LinuxHidDevice(LinuxHidDevice&& other) noexcept
        : path_(std::move(other.path_)), fd_(other.fd_)
    {
        other.fd_ = -1;
    }

    LinuxHidDevice& LinuxHidDevice::operator=(LinuxHidDevice&& other) noexcept
    {
        if (this != &other)
        {
            close();

            path_ = std::move(other.path_);
            fd_ = other.fd_;
            other.fd_ = -1;
        }

        return *this;
    }

    bool LinuxHidDevice::open()
    {
        if (isOpen())
        {
            return true;
        }

        fd_ = ::open(path_.c_str(), O_RDWR | O_NONBLOCK);
        return fd_ >= 0;
    }

    void LinuxHidDevice::close()
    {
        if (fd_ >= 0)
        {
            ::close(fd_);
            fd_ = -1;
        }
    }

    bool LinuxHidDevice::isOpen() const
    {
        return fd_ >= 0;
    }

    const std::string& LinuxHidDevice::path() const
    {
        return path_;
    }

    int LinuxHidDevice::fd() const
    {
        return fd_;
    }

    bool LinuxHidDevice::writeBytes(const std::vector<std::uint8_t>& bytes) const
    {
        if (!isOpen())
        {
            return false;
        }

        const auto written = ::write(fd_, bytes.data(), bytes.size());
        return written == static_cast<ssize_t>(bytes.size());
    }

    std::vector<std::uint8_t> LinuxHidDevice::readBytes(std::size_t maxBytes) const
    {
        std::vector<std::uint8_t> buffer(maxBytes);

        if (!isOpen())
        {
            return {};
        }

        const auto bytesRead = ::read(fd_, buffer.data(), buffer.size());

        if (bytesRead <= 0)
        {
            return {};
        }

        buffer.resize(static_cast<std::size_t>(bytesRead));
        return buffer;
    }
}
