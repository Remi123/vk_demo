# Example usage:
#  mkdir b && cd b && cmake .. -GNinja && cmake --build .

cmake_minimum_required(VERSION 3.2)
cmake_policy(VERSION 3.2)

enable_testing()

# -----------------------------------------------------
# LIBRARIES DIRECTORIES 
# This is the list of the dependancies and this file should provide an easy configuration for everyone 
# -----------------------------------------------------

# Library folder
# I've decided to put some of my dependancies in the lib directory
set(lib_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/lib/)


# -----------------------------------------------------
# PROJECT  
# vkDemo is the target of the executable
# -----------------------------------------------------
project(vkDemo C CXX)

# For nice interaction with IDE
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# -----------------------------------------------------
# COMPILER OPTIONS
# -----------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()



file(GLOB sources main.cpp )

# Executable target to link libraries and include directories
add_executable(vkDemo ${sources} )
add_subdirectory(src)

set(CMAKE_CXX_CLANG_TIDY 
    clang-tidy;
    -header-filter=.;
    -checks=*;)
target_compile_features(vkDemo PUBLIC cxx_std_11)
target_compile_options(vkDemo PRIVATE 
    -Wall
    )


# -------------------------------------------------
# COMPILER WARNINGS
# -------------------------------------------------
include(cmake/compiler_warnings.cmake)
set_project_warnings(vkDemo)


# -------------------------------------------------
# CCACHE
# -------------------------------------------------
find_program(CCACHE ccache)
if(CCACHE)
    message(STATUS "using ccache")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
else()
    message(STATUS "ccache not found cannot use")
endif()

# -----------------------------------------------------
# VULKAN
# -----------------------------------------------------
include(cmake/vulkan.cmake)
target_link_libraries(vkDemo ${VULKAN_LIBRARY})

# -----------------------------------------------------
# GLFW
# -----------------------------------------------------
include(cmake/glfw.cmake)

target_include_directories(vkDemo PRIVATE ${GLFW_DIR}/include)
target_link_libraries(vkDemo glfw )
# -----------------------------------------------------
# DEAR IMGUI LIBRARY
# -----------------------------------------------------
# Headers files
include(cmake/imgui.cmake)

# -----------------------------------------------------
# GLM
# -----------------------------------------------------
include(cmake/glm.cmake)


# -----------------------------------------------------
# BOOST PACKAGE
# -----------------------------------------------------
include(cmake/boost.cmake)
target_include_directories(vkDemo PRIVATE ${Boost_INCLUDE_DIRS}
    SYSTEM PRIVATE  ${Boost_INCLUDE_DIRS})

option(NETWORK_TEST "Build and test network" TRUE)
if(NETWORK_TEST)
    add_executable(asyncserver ${CMAKE_CURRENT_SOURCE_DIR}/src/network/async_server.cpp )
    add_executable(syncclient ${CMAKE_CURRENT_SOURCE_DIR}/src/network/sync_client.cpp )

    target_include_directories(asyncserver PRIVATE ${Boost_INCLUDE_DIRS}
        SYSTEM PRIVATE  ${Boost_INCLUDE_DIRS})
    target_include_directories(syncclient PRIVATE ${Boost_INCLUDE_DIRS}                                    SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})

    target_link_libraries(asyncserver ${Boost_LIBRARIES} pthread)
    target_link_libraries(syncclient ${Boost_LIBRARIES} pthread)

    add_test(
        NAME Asynchrone_test
        COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/src/network/bash_test_Asynchrone.sh 
        )
endif()


