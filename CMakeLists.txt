cmake_minimum_required(VERSION 3.26)
project(FlexPlot)

# SET CMAKE STANDARD
set(CMAKE_CXX_STANDARD 17)

# PREPROCESSOR VARS
add_compile_definitions(IMGUI_DEFINE_MATH_OPERATORS)

# EXTRA [IMPLOT] FILES
set(IMPLOT_DEMO_SRC includes/implot_demo/implot_demo.cpp)

# HEADER ONLY LIBS
set(HEADER_ONLY_LIBS
        includes/header_only/csvparser.h
        includes/header_only/imfilebrowser.h)

# MAIN SOURCE FILES
set(SOURCE_FILES
        FlexPlot.cpp
        FlexPlot.h
        nodes.cpp
        nodes.h)

# ADD SUB-DIRECTORIES FOR BUILDING
add_subdirectory(includes/imgui_bindings)
add_subdirectory(includes/ToroImGuiHandle)
add_subdirectory(includes/ToroImNodeFlow)
add_subdirectory(includes/nativefiledialog-extended)

# MAIN EXECUTABLE
add_executable(FlexPlot main.cpp ${SOURCE_FILES} ${HEADER_ONLY_LIBS} ${IMPLOT_DEMO_SRC})

# LINK LOCAL LIBS
target_link_libraries(FlexPlot imgui_bindings)
target_link_libraries(FlexPlot ToroImGuiHandle)
target_link_libraries(FlexPlot ToroImNodeFlow)
target_link_libraries(FlexPlot nfd)

# FIND CONAN PACKAGES
find_package(imgui)
find_package(opengl_system)
find_package(implot)
find_package(glfw3)

# LINK CONAN LIBS
target_link_libraries(FlexPlot
        imgui::imgui
        opengl::opengl
        implot::implot
        glfw)
