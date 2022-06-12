cmake_minimum_required(VERSION 3.18.1)

set(CMAKE_CXX_STANDARD 20)

set (CMAKE_CXX_FLAGS "-Werror,-Wformat-security")
 
find_package(Dobby REQUIRED CONFIG)

include_directories(include)
include_directories(prefab/modules/dobby/include)

include_directories(
        ImGui
        Server/ImGui/backends
)
add_library(native-lib SHARED 
             native-lib.cpp
             ImGui/imgui.cpp
             ImGui/imgui_draw.cpp
             ImGui/imgui_demo.cpp
             ImGui/imgui_widgets.cpp 
             ImGui/imgui_tables.cpp 
             ImGui/backends/imgui_impl_opengl3.cpp)

target_link_libraries(native-lib log dobby::dobby EGL GLESv1_CM GLESv2 GLESv3)
