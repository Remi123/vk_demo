#ifndef TRI_GLOBALS_HPP
#define TRI_GLOBALS_HPP

#include <cstdint>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace tri
{
// Globals from windows
    GLFWwindow* m_window;
    uint32_t g_glfwExtensionCount = 0;
    const char** g_glfwExtensions;
    constexpr uint32_t g_window_width = 800;
    constexpr uint32_t g_window_height = 800;
}
#endif
