cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(exec)

set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sources")

add_executable(sandboxy
    ${SRC_DIR}/main.cpp
)

target_include_directories(sandboxy PUBLIC ${INC_DIR})

target_link_libraries(sandboxy PUBLIC
    sdl2
)

add_executable(test
    ${SRC_DIR}/test.cpp
)

target_include_directories(test PUBLIC ${INC_DIR})

target_link_libraries(test PUBLIC
    sdl2
)

install(TARGETS sandboxy
    RUNTIME DESTINATION bin
)