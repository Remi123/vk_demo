#ifndef PHYSICAL_DEVICE_HPP
#define PHYSICAL_DEVICE_HPP
#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <optional>
#include <iostream>

namespace tri
{
    struct physical_device
    {
        VkPhysicalDevice m_physicaldevice = VK_NULL_HANDLE;
        std::optional<uint32_t> o_iQFam;
        //
        physical_device(VkInstance inst) : o_iQFam{}
        {
            uint32_t deviceCount;
            vkEnumeratePhysicalDevices(inst,&deviceCount,nullptr);
            if(deviceCount == 0) throw std::runtime_error("Failed to find GPU with Vulkan Support");
            std::vector<VkPhysicalDevice> devices(deviceCount);
            vkEnumeratePhysicalDevices(inst,&deviceCount,devices.data());
            auto dev_ = std::find_if(devices.begin(),devices.end(),
                    [this](VkPhysicalDevice dev)
                    {
                    //
                    VkPhysicalDeviceProperties devproperties;
                    vkGetPhysicalDeviceProperties(dev,&devproperties);
                    VkPhysicalDeviceFeatures devfeatures;
                    vkGetPhysicalDeviceFeatures(dev,&devfeatures);
                    //
                    uint32_t queFamCount = 0;
                    vkGetPhysicalDeviceQueueFamilyProperties(dev,
                            &queFamCount,nullptr);
                    std::vector<VkQueueFamilyProperties> v_qfp(queFamCount);
                    vkGetPhysicalDeviceQueueFamilyProperties(dev,
                            &queFamCount, v_qfp.data());
                    uint32_t i = 0;
                    for(const auto& qf : v_qfp)
                    {
                    (qf.queueFlags & VK_QUEUE_GRAPHICS_BIT)? 
                        o_iQFam = i :  ++i;
                    };

                    return o_iQFam.has_value();
                    });

            if (dev_ == devices.end()) {
                throw std::runtime_error("failed to find a suitable GPU!");
            }
            else { 
                m_physicaldevice = std::move(*dev_);
            }

            std::cout << std::boolalpha << o_iQFam.has_value() << std::endl;
        }
        ~physical_device(){}

    };
}

#endif
