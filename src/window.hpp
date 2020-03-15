#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include "globals.hpp"

namespace tri {

struct window {
  uint32_t m_width;
  uint32_t m_height;

  //
  window()
      : m_width(800), m_height(600) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    g_glfwExtensions = glfwGetRequiredInstanceExtensions(&tri::g_glfwExtensionCount);

    m_window = glfwCreateWindow(m_width, m_height, "Vulkan", nullptr, nullptr);
          }
  ~window() {
    glfwDestroyWindow(tri::m_window);
    glfwTerminate();
  }
};
}  // namespace tri
#endif
