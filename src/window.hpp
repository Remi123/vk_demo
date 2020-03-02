#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace tri {
// Globals from windows
uint32_t g_glfwExtensionCount = 0;
const char** g_glfwExtensions;

struct window {
  GLFWwindow* m_window;
  uint32_t m_width;
  uint32_t m_height;
  //
  window() : m_width(800), m_height(600) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    g_glfwExtensions = glfwGetRequiredInstanceExtensions(&g_glfwExtensionCount);
    m_window = glfwCreateWindow(m_width, m_height, "Vulkan", nullptr, nullptr);
  }
  ~window() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
  }
};
}  // namespace tri
