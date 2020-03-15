#ifndef PHYSICAL_DEVICE_HPP
#define PHYSICAL_DEVICE_HPP
#include <algorithm>
#include <iostream>
#include <optional>
#include <set>
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan.h>

namespace tri {
struct physical_device {
  VkPhysicalDevice m_physicaldevice = VK_NULL_HANDLE;
  std::optional<uint32_t> o_iQFam;
  std::optional<uint32_t> o_prQFam;
  const std::vector<const char *> m_deviceExtensions;
  //
  struct swapchain_support_detail {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
    ;
  };
  //

  physical_device(tri::instance &inst)
      : o_iQFam{}, o_prQFam{}, m_deviceExtensions{
                                   VK_KHR_SWAPCHAIN_EXTENSION_NAME} {
    uint32_t deviceCount;
    vkEnumeratePhysicalDevices(inst.m_instance, &deviceCount, nullptr);
    if (deviceCount == 0)
      throw std::runtime_error("Failed to find GPU with Vulkan Support");
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(inst.m_instance, &deviceCount, devices.data());
    auto dev_ = std::find_if(
        devices.begin(), devices.end(), [this, &inst](VkPhysicalDevice dev) {
          bool swapChainAdequate = false;

          bool extensionsSupported = this->checkDeviceExtensionSupport(dev);

          if (extensionsSupported) {
            swapchain_support_detail swapChainSupport =
                this->querySwapchainSupport(dev, inst.m_surface);
            swapChainAdequate = !swapChainSupport.formats.empty() &&
                                !swapChainSupport.presentModes.empty();
          }

          if (extensionsSupported && swapChainAdequate)
            return false;

          //
          uint32_t queFamCount = 0;
          vkGetPhysicalDeviceQueueFamilyProperties(dev, &queFamCount, nullptr);
          std::vector<VkQueueFamilyProperties> v_qfp(queFamCount);
          vkGetPhysicalDeviceQueueFamilyProperties(dev, &queFamCount,
                                                   v_qfp.data());
          VkBool32 presentSupport = false;
          uint32_t i = 0;
          for (const auto &qf : v_qfp) {
            if (qf.queueFlags & VK_QUEUE_GRAPHICS_BIT)
              o_iQFam = i;

            vkGetPhysicalDeviceSurfaceSupportKHR(dev, i, inst.m_surface,
                                                 &presentSupport);
            if (presentSupport)
              o_prQFam = i;
            ++i;
          };

          return o_iQFam.has_value() && o_prQFam.has_value();
        });

    if (dev_ == devices.end()) {
      throw std::runtime_error("failed to find a suitable GPU!");
    } else {
      m_physicaldevice = std::move(*dev_);
    }

    std::cout << std::boolalpha << o_iQFam.has_value() << std::endl;
  }
  ~physical_device() {}

  swapchain_support_detail querySwapchainSupport(VkPhysicalDevice dev_,
                                                 VkSurfaceKHR &surface_) {
    swapchain_support_detail details;
    uint32_t formatCount;
    uint32_t presentModeCount;
    //
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev_, surface_,
                                              &details.capabilities);
    vkGetPhysicalDeviceSurfaceFormatsKHR(dev_, surface_, &formatCount, nullptr);
    vkGetPhysicalDeviceSurfacePresentModesKHR(dev_, surface_, &presentModeCount,
                                              nullptr);
    //
    if (formatCount) {
      details.formats.resize(formatCount);
      vkGetPhysicalDeviceSurfaceFormatsKHR(dev_, surface_, &formatCount,
                                           details.formats.data());
    }
    //
    if (presentModeCount != 0) {
      details.presentModes.resize(presentModeCount);
      vkGetPhysicalDeviceSurfacePresentModesKHR(
          dev_, surface_, &presentModeCount, details.presentModes.data());
    }

    return details;
  }

  bool checkDeviceExtensionSupport(VkPhysicalDevice device) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,
                                         nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,
                                         availableExtensions.data());

    std::set<std::string> requiredExtensions(m_deviceExtensions.begin(),
                                             m_deviceExtensions.end());

    for (const auto &extension : availableExtensions) {
      requiredExtensions.erase(extension.extensionName);
    }

    return !requiredExtensions.empty();
  }
};
} // namespace tri

#endif
