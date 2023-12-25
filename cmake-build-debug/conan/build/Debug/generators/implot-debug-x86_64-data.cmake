########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(implot_COMPONENT_NAMES "")
list(APPEND implot_FIND_DEPENDENCY_NAMES imgui)
list(REMOVE_DUPLICATES implot_FIND_DEPENDENCY_NAMES)
set(imgui_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(implot_PACKAGE_FOLDER_DEBUG "C:/Users/admin/.conan2/p/b/implo5b9747c9786cd/p")
set(implot_BUILD_MODULES_PATHS_DEBUG )


set(implot_INCLUDE_DIRS_DEBUG "${implot_PACKAGE_FOLDER_DEBUG}/include")
set(implot_RES_DIRS_DEBUG )
set(implot_DEFINITIONS_DEBUG )
set(implot_SHARED_LINK_FLAGS_DEBUG )
set(implot_EXE_LINK_FLAGS_DEBUG )
set(implot_OBJECTS_DEBUG )
set(implot_COMPILE_DEFINITIONS_DEBUG )
set(implot_COMPILE_OPTIONS_C_DEBUG )
set(implot_COMPILE_OPTIONS_CXX_DEBUG )
set(implot_LIB_DIRS_DEBUG "${implot_PACKAGE_FOLDER_DEBUG}/lib")
set(implot_BIN_DIRS_DEBUG )
set(implot_LIBRARY_TYPE_DEBUG STATIC)
set(implot_IS_HOST_WINDOWS_DEBUG 1)
set(implot_LIBS_DEBUG implot)
set(implot_SYSTEM_LIBS_DEBUG )
set(implot_FRAMEWORK_DIRS_DEBUG )
set(implot_FRAMEWORKS_DEBUG )
set(implot_BUILD_DIRS_DEBUG )
set(implot_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(implot_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${implot_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${implot_COMPILE_OPTIONS_C_DEBUG}>")
set(implot_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${implot_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${implot_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${implot_EXE_LINK_FLAGS_DEBUG}>")


set(implot_COMPONENTS_DEBUG )