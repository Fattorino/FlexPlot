cmake_minimum_required(VERSION 3.26)

# CREATE PROJECT
project(ToroImGuiHandle C CXX)

# SET SOURCE FILES FOR PROJECT
set(SOURCE_FILES
        ToroImGuiHandle.cpp
        ToroImGuiHandle.h)

# CREATE LIBRARY FROM SOURCE_FILES
add_library(ToroImGuiHandle SHARED STATIC ${SOURCE_FILES})

# LINK LOCAL LIBS
target_link_libraries(ToroImGuiHandle imgui_bindings)

# FIND CONAN PACKAGES
find_package(imgui)
find_package(opengl_system)
find_package(glfw3)

# LINK CONAN LIBS
target_link_libraries(ToroImGuiHandle
        imgui::imgui
        opengl::opengl
        glfw)
