#ifndef TRI_SWAPCHAIN_HPP
#define TRI_SWAPCHAIN_HPP

#include <cstdint> // Necessary for UINT32_MAX
#include <vector>
#include <vulkan/vulkan.h>

#include "globals.hpp"
#include "physicaldevice.hpp"

namespace tri {
struct swapchain {

  //
  struct swapchain_support_detail {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
  };
  //

  swapchain(tri::instance& inst_,tri::physical_device &physdev_) {
    swapchain_support_detail swapdetail_;
    VkSurfaceFormatKHR surfaceFormat =
        chooseSwapSurfaceFormat(swapdetail_.formats);
    VkPresentModeKHR presentMode =
        chooseSwapPresentMode(swapdetail_.presentModes);
    VkExtent2D extent2d = chooseSwapExtent(swapdetail_.capabilities);
    // Infos are retrieve, let's setup correctly
    uint32_t imageCount =
        swapdetail_.capabilities.minImageCount + 1; // one more

    if (swapdetail_.capabilities.maxImageCount > 0 &&
        imageCount > swapdetail_.capabilities.maxImageCount) {
      imageCount = swapdetail_.capabilities.maxImageCount;
    }
// Create Info

    VkSwapchainCreateInfoKHR swch_ci = {};
    swch_ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swch_ci.surface = inst_.m_surface;
    swch_ci.minImageCount = imageCount;
    swch_ci.imageFormat = surfaceFormat.format;
    swch_ci.imageColorSpace = surfaceFormat.colorSpace;
    swch_ci.imageExtent = extent2d;
    swch_ci.imageArrayLayers = 1;
    swch_ci.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // Optional
        createInfo.pQueueFamilyIndices = nullptr; // Optional
    }

    // TODO Continue here

  }

  ~swapchain() {}

  VkSurfaceFormatKHR chooseSwapSurfaceFormat(
      const std::vector<VkSurfaceFormatKHR> &availableFormats) {
    for (const auto &availableFormat : availableFormats) {
      if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
          availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
        return availableFormat;
      }
    }

    return availableFormats[0];
  }

  VkPresentModeKHR chooseSwapPresentMode(
      const std::vector<VkPresentModeKHR> &availablePresentModes) {
    for (const auto &availablePresentMode : availablePresentModes) {
      if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
        return availablePresentMode;
      }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
  }

  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities) {
    if (capabilities.currentExtent.width != UINT32_MAX) {
      return capabilities.currentExtent;
    } else {
      VkExtent2D actualExtent = {tri::g_window_width, tri::g_window_height};

      actualExtent.width = std::max(
          capabilities.minImageExtent.width,
          std::min(capabilities.maxImageExtent.width, actualExtent.width));
      actualExtent.height = std::max(
          capabilities.minImageExtent.height,
          std::min(capabilities.maxImageExtent.height, actualExtent.height));

      return actualExtent;
    }
  }
};
} // namespace tri

#endif
