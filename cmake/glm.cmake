message(STATUS "GLM.cmake Configuration")

set(GLM_DIR ${lib_FOLDER}/glm/)

target_include_directories(vkDemo PRIVATE ${GLM_DIR})

message(STATUS "End GLM.cmake")
