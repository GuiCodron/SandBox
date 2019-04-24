cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(sdl2)
include(ExternalProject)

ExternalProject_Add(
    sdl2_ext
    URL "${VENDOR_DIR}/SDL2-2.0.8/SDL2-2.0.8.zip"
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR>
    BUILD_COMMAND make -j9
)

ExternalProject_Get_Property(sdl2_ext INSTALL_DIR)

add_library(sdl2 STATIC IMPORTED GLOBAL)
add_dependencies(sdl2 sdl2_ext)

set_target_properties(sdl2 PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lib/libSDL2.a
    INTERFACE_INCLUDE_DIRECTORIES ${INSTALL_DIR}/include/SDL2
)

get_target_property(includes sdl2 INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "sdl2 includes ${includes}")