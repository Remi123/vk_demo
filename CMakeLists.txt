# Example usage:
#  mkdir b && cd b && cmake .. -GNinja && cmake --build .

cmake_minimum_required(VERSION 3.2)
cmake_policy(VERSION 3.2)


# -----------------------------------------------------
# LIBRARIES DIRECTORIES 
# This is the list of the dependancies and this file should provide an easy configuration for everyone 
# -----------------------------------------------------
# Boost
	set(Boost_INCLUDE_DIR /home/mariefrance/Documents/SDKs/boost/)
	# find_package(boost) will do the rest
# Dear ImGui
	set(IMGUI_DIR /home/mariefrance/Documents/SDKs/imgui)
# GLFW
	set(GLFW_DIR /home/mariefrance/Documents/SDKs/glfw/)
# Vulkan
	# For Vulkan we are relying on CMake's find_library
# GLM
	set(GLM_DIR /home/mariefrance/Documents/SDKs/glm/)



# -----------------------------------------------------
# PROJECT  
# vkDemo is the target of the executable
# -----------------------------------------------------
project(vkDemo C CXX)



# -----------------------------------------------------
# COMPILER OPTIONS
# -----------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVK_PROTOTYPES")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_PROTOTYPES")

file(GLOB sources *.cpp )
	# Executable target to link libraries and include directories
add_executable(vkDemo ${sources} )



# -----------------------------------------------------
# VULKAN
# -----------------------------------------------------
find_library(VULKAN_LIBRARY
  NAMES vulkan vulkan-1)
set(LIBRARIES "glfw;${VULKAN_LIBRARY}")
target_link_libraries(vkDemo ${VULKAN_LIBRARY})
message(STATUS "Vulkan version: ${VULKAN_INCLUDE_DIRS} ${Vulkan_INCLUDE_DIR}")



# -----------------------------------------------------
# GLFW
# -----------------------------------------------------
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
add_subdirectory(${GLFW_DIR} binary_dir EXCLUDE_FROM_ALL)
target_include_directories(vkDemo PRIVATE ${GLFW_DIR}/include)
	# Use vulkan headers from glfw:
	include_directories(${GLFW_DIR}/deps)
target_link_libraries(vkDemo glfw )



# -----------------------------------------------------
# DEAR IMGUI LIBRARY
# -----------------------------------------------------
	# Headers files
target_include_directories(vkDemo PRIVATE 
	${IMGUI_DIR} # For imgui.h and imgui_*.h
	${IMGUI_DIR}/examples # for imgui_impl_vulkan.h and imgui_impl_glfw.h
)

	# sources files
target_sources( vkDemo PUBLIC
	${IMGUI_DIR}/examples/imgui_impl_glfw.cpp 
	${IMGUI_DIR}/examples/imgui_impl_vulkan.cpp
	${IMGUI_DIR}/imgui.cpp 
	${IMGUI_DIR}/imgui_draw.cpp 
	${IMGUI_DIR}/imgui_demo.cpp 
	${IMGUI_DIR}/imgui_widgets.cpp
)



# -----------------------------------------------------
# GLM
# -----------------------------------------------------
target_include_directories(vkDemo PRIVATE ${GLM_DIR})



# -----------------------------------------------------
# BOOST PACKAGE
# -----------------------------------------------------
find_package(Boost 1.72 REQUIRED)
if(Boost_FOUND)
	target_include_directories(vkDemo PRIVATE ${Boost_INCLUDE_DIRS})
endif()
message(STATUS "Boost version: ${Boost_VERSION}")






