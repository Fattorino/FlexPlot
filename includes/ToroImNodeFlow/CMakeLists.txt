cmake_minimum_required(VERSION 3.26)

# CREATE PROJECT
project(ToroImNodeFlow C CXX)

# SET SOURCE FILES FOR PROJECT
file(GLOB_RECURSE _HDRS "include/*.h")
file(GLOB_RECURSE _SRCS "src/*.cpp")
file(GLOB_RECURSE _IMNODEEDITOR "ImNodeEditor/*.cpp" "ImNodeEditor/*.h" "ImNodeEditor/*.inl")

# CREATE LIBRARY FROM SOURCE_FILES
add_library(ToroImNodeFlow SHARED STATIC ${_SRCS} ${_HDRS} ${_IMNODEEDITOR})

# FIND CONAN PACKAGES
find_package(imgui)

# LINK CONAN LIBS
target_link_libraries(ToroImNodeFlow imgui::imgui)

# PREP TO USE "#include <>"
target_include_directories(ToroImNodeFlow PUBLIC include)
