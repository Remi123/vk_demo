#ifndef TRI_LOGICAL_DEVICE_HPP
#define TRI_LOGICAL_DEVICE_HPP
#include "globals.hpp"
#include "instance.hpp"
#include "physicaldevice.hpp"
#include <set>
#include <vector>
#include <optional>
#include <vulkan/vulkan.h>

namespace tri {
struct logical_device {
  std::optional<uint32_t> o_iqf;
  VkDeviceQueueCreateInfo m_devqueue_ci;
  VkPhysicalDeviceFeatures m_dev_features;
  VkDeviceCreateInfo m_dev_ci;
  VkDevice m_dev;
  VkQueue m_queue;

  float m_qpriority;

  //
  logical_device(const physical_device &phy_dev)
      : o_iqf(phy_dev.o_iQFam), m_devqueue_ci{},
        m_dev_features{}, m_dev_ci{}, m_dev{}, m_queue{}, m_qpriority{1.0f} {
    m_devqueue_ci.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    m_devqueue_ci.queueFamilyIndex = phy_dev.o_iQFam.value();
    m_devqueue_ci.queueCount = 1;
    m_devqueue_ci.pQueuePriorities = &m_qpriority;

    m_dev_ci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    m_dev_ci.pQueueCreateInfos = &m_devqueue_ci; // Might be wrong
    m_dev_ci.queueCreateInfoCount = 1;
    m_dev_ci.pEnabledFeatures = &m_dev_features;

    if (enableValidationLayers) {

      m_dev_ci.enabledLayerCount = tri::instance::validationLayers.size();
      m_dev_ci.ppEnabledLayerNames = tri::instance::validationLayers.data();

      for (const auto &p : tri::instance::validationLayers) {
        std::cout << p << std::endl;
      }
    } else {
      m_dev_ci.enabledLayerCount = 0;
    }

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {phy_dev.o_iQFam.value(),
                                              phy_dev.o_prQFam.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
      VkDeviceQueueCreateInfo queueCreateInfo = {};
      queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      queueCreateInfo.queueFamilyIndex = queueFamily;
      queueCreateInfo.queueCount = 1;
      queueCreateInfo.pQueuePriorities = &queuePriority;
      queueCreateInfos.push_back(queueCreateInfo);
    }

    m_dev_ci.queueCreateInfoCount =
        static_cast<uint32_t>(queueCreateInfos.size());
    m_dev_ci.pQueueCreateInfos = queueCreateInfos.data();
    m_dev_ci.enabledExtensionCount =
        static_cast<uint32_t>(phy_dev.m_deviceExtensions.size());
    m_dev_ci.ppEnabledExtensionNames = phy_dev.m_deviceExtensions.data();

    if (vkCreateDevice(phy_dev.m_physicaldevice, &m_dev_ci, nullptr, &m_dev) !=
        VK_SUCCESS) {
      throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(m_dev, phy_dev.o_prQFam.value(), 0, &m_queue);
  }
  ~logical_device() { vkDestroyDevice(m_dev, nullptr); }
};
} // namespace tri

#endif
