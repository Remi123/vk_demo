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
}
#endif
