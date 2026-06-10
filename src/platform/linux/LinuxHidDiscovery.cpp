#include "peripheralos/platform/linux/LinuxHidDiscovery.hpp"

#include <libudev.h>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace peripheralos::platform::linux
{
    namespace
    {
        void applyUeventInfo(const std::string& devnode, HidDeviceInfo& info)
        {
            const auto hidrawName = std::filesystem::path(devnode).filename().string();
            const auto ueventPath =
                std::filesystem::path("/sys/class/hidraw") / hidrawName / "device" / "uevent";

            std::ifstream file(ueventPath);

            if (!file.is_open())
            {
                return;
            }

            std::string line;

            while (std::getline(file, line))
            {
                if (line.rfind("HID_ID=", 0) == 0)
                {
                    const auto value = line.substr(7);

                    unsigned int bus = 0;
                    unsigned int vendor = 0;
                    unsigned int product = 0;

                    if (std::sscanf(value.c_str(), "%x:%x:%x", &bus, &vendor, &product) == 3)
                    {
                        info.busType = bus;
                        info.vendorId = static_cast<std::uint16_t>(vendor);
                        info.productId = static_cast<std::uint16_t>(product);
                    }
                }

                if (line.rfind("HID_NAME=", 0) == 0)
                {
                    info.name = line.substr(9);
                }
            }
        }

        std::string safeString(const char* value)
        {
            return value == nullptr ? "" : std::string(value);
        }

        std::uint16_t parseHex16(const char* value)
        {
            if (value == nullptr)
            {
                return 0;
            }

            return static_cast<std::uint16_t>(std::strtoul(value, nullptr, 16));
        }

        std::string getSysAttr(udev_device* device, const char* key)
        {
            if (device == nullptr)
            {
                return "";
            }

            return safeString(udev_device_get_sysattr_value(device, key));
        }

        void applyHidParentInfo(udev_device* hidParent, HidDeviceInfo& info)
        {
            if (hidParent == nullptr)
            {
                return;
            }

            const auto hidName = getSysAttr(hidParent, "name");
            const auto hidPhys = getSysAttr(hidParent, "phys");
            const char* hidId = udev_device_get_sysattr_value(hidParent, "hid_id");

            if (!hidName.empty())
            {
                info.name = hidName;
            }

            if (!hidPhys.empty())
            {
                info.physicalPath = hidPhys;
            }

            if (hidId != nullptr)
            {
                unsigned int bus = 0;
                unsigned int vendor = 0;
                unsigned int product = 0;

                if (std::sscanf(hidId, "%x:%x:%x", &bus, &vendor, &product) == 3)
                {
                    info.busType = bus;
                    info.vendorId = static_cast<std::uint16_t>(vendor);
                    info.productId = static_cast<std::uint16_t>(product);
                }
            }
        }

        void applyUsbParentFallback(udev_device* usbParent, HidDeviceInfo& info)
        {
            if (usbParent == nullptr)
            {
                return;
            }

            if (info.name.empty())
            {
                const auto product = getSysAttr(usbParent, "product");
                const auto manufacturer = getSysAttr(usbParent, "manufacturer");

                if (!manufacturer.empty() && !product.empty())
                {
                    info.name = manufacturer + " " + product;
                }
                else if (!product.empty())
                {
                    info.name = product;
                }
            }

            if (info.vendorId == 0)
            {
                info.vendorId = parseHex16(udev_device_get_sysattr_value(usbParent, "idVendor"));
            }

            if (info.productId == 0)
            {
                info.productId = parseHex16(udev_device_get_sysattr_value(usbParent, "idProduct"));
            }
        }
    }

    std::vector<HidDeviceInfo> LinuxHidDiscovery::discover() const
    {
        std::vector<HidDeviceInfo> devices;

        udev* rawUdev = udev_new();

        if (rawUdev == nullptr)
        {
            throw std::runtime_error("Failed to initialize udev");
        }

        std::unique_ptr<udev, decltype(&udev_unref)> udevHandle(rawUdev, udev_unref);

        udev_enumerate* rawEnumerate = udev_enumerate_new(udevHandle.get());

        if (rawEnumerate == nullptr)
        {
            throw std::runtime_error("Failed to initialize udev enumerate");
        }

        std::unique_ptr<udev_enumerate, decltype(&udev_enumerate_unref)> enumerateHandle(
            rawEnumerate,
            udev_enumerate_unref
        );

        udev_enumerate_add_match_subsystem(enumerateHandle.get(), "hidraw");
        udev_enumerate_scan_devices(enumerateHandle.get());

        udev_list_entry* entries = udev_enumerate_get_list_entry(enumerateHandle.get());
        udev_list_entry* entry = nullptr;

        udev_list_entry_foreach(entry, entries)
        {
            const char* syspath = udev_list_entry_get_name(entry);

            if (syspath == nullptr)
            {
                continue;
            }

            udev_device* rawDevice = udev_device_new_from_syspath(udevHandle.get(), syspath);

            if (rawDevice == nullptr)
            {
                continue;
            }

            std::unique_ptr<udev_device, decltype(&udev_device_unref)> deviceHandle(
                rawDevice,
                udev_device_unref
            );

            const char* devnode = udev_device_get_devnode(deviceHandle.get());

            if (devnode == nullptr)
            {
                continue;
            }

            HidDeviceInfo info;
            info.path = safeString(devnode);
            applyUeventInfo(info.path, info);

            udev_device* hidParent = udev_device_get_parent_with_subsystem_devtype(
                deviceHandle.get(),
                "hid",
                nullptr
            );

            applyHidParentInfo(hidParent, info);

            udev_device* usbParent = udev_device_get_parent_with_subsystem_devtype(
                deviceHandle.get(),
                "usb",
                "usb_device"
            );

            applyUsbParentFallback(usbParent, info);

            devices.push_back(info);
        }

        return devices;
    }
}
