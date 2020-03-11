#ifndef TRI_LOGICAL_DEVICE_HPP
#define TRI_LOGICAL_DEVICE_HPP
#include "globals.hpp"
#include "instance.hpp"
#include "physicaldevice.hpp"

namespace tri {
struct logical_device {
  std::optional<uint32_t> o_iqf;
  VkDeviceQueueCreateInfo m_dev_queue;
  VkPhysicalDeviceFeatures m_dev_features;
  VkDeviceCreateInfo m_dev_info;
  VkDevice m_dev;
  VkQueue m_queue;
  float m_qpriority;
  //
  logical_device(const physical_device& phy_dev)
      : o_iqf(phy_dev.o_iQFam),
        m_dev_queue{},
        m_dev_features{},
        m_dev_info{},
        m_dev{},
        m_queue{},
        m_qpriority{1.0f} {
    m_dev_queue.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    m_dev_queue.queueFamilyIndex = phy_dev.o_iQFam.value();
    m_dev_queue.queueCount = 1;
    m_dev_queue.pQueuePriorities = &m_qpriority;

    m_dev_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    m_dev_info.pQueueCreateInfos = &m_dev_queue;  // Might be wrong
    m_dev_info.queueCreateInfoCount = 1;
    m_dev_info.pEnabledFeatures = &m_dev_features;

    m_dev_info.enabledExtensionCount = 0;

    if (enableValidationLayers) {
      m_dev_info.enabledLayerCount = tri::instance::validationLayers.size();
      m_dev_info.ppEnabledLayerNames = tri::instance::validationLayers.data();
      for (const auto& p : tri::instance::validationLayers) {
        std::cout << p << std::endl;
      }
    } else {
      m_dev_info.enabledLayerCount = 0;
    }
    if (vkCreateDevice(phy_dev.m_physicaldevice, &m_dev_info, nullptr,
                       &m_dev) != VK_SUCCESS) {
      throw std::runtime_error("failed to create logical device!");
    }
    vkGetDeviceQueue(m_dev, phy_dev.o_iQFam.value(), 0, &m_queue);
  }
  ~logical_device() { vkDestroyDevice(m_dev, nullptr); }
};
}  // namespace tri

#endif
