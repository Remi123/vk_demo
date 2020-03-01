message(STATUS "glfw.cmake Configuration")

set(GLFW_DIR ${lib_FOLDER}/glfw/)

option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
# Includes
add_subdirectory(${GLFW_DIR} binary_dir EXCLUDE_FROM_ALL)
# Use vulkan headers from glfw:
include_directories(${GLFW_DIR}/deps)

message(STATUS "End glfw.cmake")
