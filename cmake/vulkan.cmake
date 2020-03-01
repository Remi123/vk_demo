message(STATUS "Vulkan.cmake Configuration")

find_library(VULKAN_LIBRARY
        NAMES vulkan vulkan-1)

message(STATUS "Vulkan path:" ${VULKAN_LIBRARY})

message(STATUS "End Vulkan.cmake")
