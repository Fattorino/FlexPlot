cmake_minimum_required(VERSION 3.26)
project(FlexPlot)

# SET CMAKE STANDARD
set(CMAKE_CXX_STANDARD 17)

# PREPROCESSOR VARS
add_compile_definitions(IMGUI_DEFINE_MATH_OPERATORS)

# EXTRA [IMPLOT] FILES
set(IMPLOT_DEMO_SRC includes/implot_demo/implot_demo.cpp)

# HEADER ONLY LIBS
file(GLOB_RECURSE _HDRS_ONLY "includes/header_only/*.hpp" "includes/header_only/*.h")

# MAIN SOURCE FILES
file(GLOB_RECURSE _SRCS "src/*.cpp" "src/*.h")

# ADD SUB-DIRECTORIES FOR BUILDING
add_subdirectory(includes/ToroImGuiHandle)
add_subdirectory(includes/ToroImNodeFlow)
add_subdirectory(includes/nativefiledialog-extended)

# MAIN EXECUTABLE
add_executable(FlexPlot src/main.cpp ${_SRCS} ${_HDRS_ONLY} ${IMPLOT_DEMO_SRC})

# LINK LOCAL LIBS
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

# ADD HEADERS ONLY LIBS TO "#include <>"
target_include_directories(FlexPlot PUBLIC includes/header_only)
