cmake_minimum_required(VERSION 3.2)
cmake_policy(VERSION 3.2)

target_sources (vkDemo PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}/window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/instance.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/application.hpp


    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/graphics.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/graphics.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/network/network.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/network/network.cpp
    )

