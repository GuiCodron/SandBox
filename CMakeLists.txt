cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Sandboxy VERSION 0.1 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Os -Wall -pedantic ")
set(sdl_compile_options "-lm -liconv  -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${sdl_compile_options}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-command-line-argument")

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/exec)

#include(cmake/includes.cmake)
set(VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendors)

add_subdirectory(externals)
add_subdirectory(sandboxy)
