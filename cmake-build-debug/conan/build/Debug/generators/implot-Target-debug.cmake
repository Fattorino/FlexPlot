# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(implot_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(implot_FRAMEWORKS_FOUND_DEBUG "${implot_FRAMEWORKS_DEBUG}" "${implot_FRAMEWORK_DIRS_DEBUG}")

set(implot_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET implot_DEPS_TARGET)
    add_library(implot_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET implot_DEPS_TARGET
             PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${implot_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${implot_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:imgui::imgui>
             APPEND)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### implot_DEPS_TARGET to all of them
conan_package_library_targets("${implot_LIBS_DEBUG}"    # libraries
                              "${implot_LIB_DIRS_DEBUG}" # package_libdir
                              "${implot_BIN_DIRS_DEBUG}" # package_bindir
                              "${implot_LIBRARY_TYPE_DEBUG}"
                              "${implot_IS_HOST_WINDOWS_DEBUG}"
                              implot_DEPS_TARGET
                              implot_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "implot"    # package_name
                              "${implot_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${implot_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Debug ########################################
    set_property(TARGET implot::implot
                 PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Debug>:${implot_OBJECTS_DEBUG}>
                 $<$<CONFIG:Debug>:${implot_LIBRARIES_TARGETS}>
                 APPEND)

    if("${implot_LIBS_DEBUG}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET implot::implot
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     implot_DEPS_TARGET
                     APPEND)
    endif()

    set_property(TARGET implot::implot
                 PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Debug>:${implot_LINKER_FLAGS_DEBUG}> APPEND)
    set_property(TARGET implot::implot
                 PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Debug>:${implot_INCLUDE_DIRS_DEBUG}> APPEND)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET implot::implot
                 PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Debug>:${implot_LIB_DIRS_DEBUG}> APPEND)
    set_property(TARGET implot::implot
                 PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Debug>:${implot_COMPILE_DEFINITIONS_DEBUG}> APPEND)
    set_property(TARGET implot::implot
                 PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Debug>:${implot_COMPILE_OPTIONS_DEBUG}> APPEND)

########## For the modules (FindXXX)
set(implot_LIBRARIES_DEBUG implot::implot)
