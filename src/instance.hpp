#include "vulkan/vulkan.hpp"
//#include "window.hpp"

namespace tri {
struct instance {
  VkInstance m_instance;
  VkInstanceCreateInfo m_inst_create_info;

  instance() : m_instance{}, m_inst_create_info{} {
    VkApplicationInfo m_appinfo;
    m_appinfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    m_appinfo.pApplicationName = "Hello Triangle";
    m_appinfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    m_appinfo.pEngineName = "No Engine";
    m_appinfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    m_appinfo.apiVersion = VK_API_VERSION_1_0;
    //
    m_inst_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    m_inst_create_info.pApplicationInfo = &m_appinfo;
    //
    m_inst_create_info.enabledExtensionCount = tri::g_glfwExtensionCount;
    m_inst_create_info.ppEnabledExtensionNames = tri::g_glfwExtensions;
    //
    // This might change soon
    m_inst_create_info.enabledLayerCount = 0;
    //
    if (vkCreateInstance(&m_inst_create_info, nullptr, &m_instance) !=
        VK_SUCCESS) {
      throw std::runtime_error("failed to create instance!");
    }
  }
  ~instance() { vkDestroyInstance(m_instance, nullptr); }
};
}  // namespace tri
