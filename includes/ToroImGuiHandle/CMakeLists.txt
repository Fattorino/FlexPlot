cmake_minimum_required(VERSION 3.26)

# CREATE PROJECT
project(ToroImGuiHandle C CXX)

# SET SOURCE FILES FOR PROJECT
file(GLOB_RECURSE _HDRS "include/*.hpp" "include/*.h")
file(GLOB_RECURSE _SRCS "src/*.cpp")
file(GLOB_RECURSE _IMGUI_BINDINGS "imgui_bindings/*.cpp" "imgui_bindings/*.h")

# CREATE LIBRARY FROM SOURCE_FILES
add_library(ToroImGuiHandle SHARED STATIC ${_SRCS} ${_HDRS} ${_IMGUI_BINDINGS})

# FIND CONAN PACKAGES
find_package(imgui)
find_package(opengl_system)
find_package(glfw3)

# LINK CONAN LIBS
target_link_libraries(ToroImGuiHandle
        imgui::imgui
        opengl::opengl
        glfw)

# PREP TO USE "#include <>"
target_include_directories(ToroImGuiHandle PUBLIC include)
