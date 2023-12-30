cmake_minimum_required(VERSION 3.26)

# CREATE PROJECT
project(imgui_bindings C CXX)

# SET SOURCE FILES FOR PROJECT
set(SOURCE_FILES
        imgui_impl_glfw.cpp
        imgui_impl_glfw.h
        imgui_impl_opengl3.cpp
        imgui_impl_opengl3.h
        imgui_impl_opengl3_loader.h
        imgui_stdlib.cpp
        imgui_stdlib.h)

# CREATE LIBRARY FROM SOURCE_FILES
add_library(imgui_bindings SHARED STATIC ${SOURCE_FILES})

# FIND CONAN PACKAGES
find_package(imgui)
find_package(opengl_system)
find_package(glfw3)

# LINK CONAN LIBS
target_link_libraries(imgui_bindings
        imgui::imgui
        opengl::opengl
        glfw)