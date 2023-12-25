cmake_minimum_required(VERSION 3.26)

# CREATE PROJECT
project(ToroImNodeFlow C CXX)

# SET SOURCE FILES FOR PROJECT
set(SOURCE_FILES
        ToroImNodeFlow.cpp
        ToroImNodeFlow.h ImNodeEditor/crude_json.cpp
        ImNodeEditor/crude_json.h
        ImNodeEditor/imgui_bezier_math.h
        ImNodeEditor/imgui_bezier_math.inl
        ImNodeEditor/imgui_canvas.cpp
        ImNodeEditor/imgui_canvas.h
        ImNodeEditor/imgui_extra_math.h
        ImNodeEditor/imgui_extra_math.inl
        ImNodeEditor/imgui_node_editor.cpp
        ImNodeEditor/imgui_node_editor.h
        ImNodeEditor/imgui_node_editor_api.cpp
        ImNodeEditor/imgui_node_editor_internal.h
        ImNodeEditor/imgui_node_editor_internal.inl)

# CREATE LIBRARY FROM SOURCE_FILES
add_library(ToroImNodeFlow SHARED STATIC ${SOURCE_FILES})

# FIND CONAN PACKAGES
find_package(imgui)

# LINK CONAN LIBS
target_link_libraries(ToroImNodeFlow imgui::imgui)
