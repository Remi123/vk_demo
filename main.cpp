// dear imgui: standalone example application for Glfw + Vulkan
// If you are new to dear imgui, see examples/README.txt and documentation at
// the top of imgui.cpp.

// Important note to the reader who wish to integrate imgui_impl_vulkan.cpp/.h
// in their own engine/app.
// - Common ImGui_ImplVulkan_XXX functions and structures are used to interface
// with imgui_impl_vulkan.cpp/.h.
//   You will use those if you want to use this rendering back-end in your
//   engine/app.
// - Helper ImGui_ImplVulkanH_XXX functions and structures are only used by this
// example (main.cpp) and by
//   the back-end itself (imgui_impl_vulkan.cpp), but should PROBABLY NOT be
//   used by your own engine/app code.
// Read comments in imgui_impl_vulkan.h.

#include "src/application.hpp"
//#include "src/graphics.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

//#include "src/network.hpp"

int main(int, char**) {
  // net::server{};
  // visual::graphics Grp{};
  // Grp.run();

  tri::application app{};
  // debug info
  {
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
                                           extensions.data());
    std::cout << "available extensions:" << std::endl;

    for (const auto& extension : extensions) {
      std::cout << "\t" << extension.extensionName << std::endl;
    }
  }
  //
  try {
    app.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
