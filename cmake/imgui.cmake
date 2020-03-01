message(STATUS "ImGui.cmake Configuration")

set(IMGUI_DIR ${lib_FOLDER}/imgui/)

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

message(STATUS "End ImGui.cmake ")


