#ifndef VKDEMO_GRAPHICS_HPP
#define VKDEMO_GRAPHICS_HPP

#include <stdio.h>   // printf, fprintf
#include <stdlib.h>  // abort

#include <algorithm>
#include <numeric>
#include <vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

namespace visual {
struct graphics {
  graphics();
  ~graphics();
  void run();

 private:
  GLFWwindow* m_glfw_window;
  VkResult err;
  ImGui_ImplVulkanH_Window* wd;
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};
};      // namespace visual
#endif  // VKDEMO_GRAPHICS_HPP
