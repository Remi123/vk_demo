cmake_minimum_required(VERSION 3.2)
#cmake_policy(VERSION 3.2)

target_sources (vkDemo PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/graphics.hpp
         ${CMAKE_CURRENT_SOURCE_DIR}/graphics.cpp

          ${CMAKE_CURRENT_SOURCE_DIR}/network.hpp
          ${CMAKE_CURRENT_SOURCE_DIR}/network.cpp
          )
