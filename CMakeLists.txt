cmake_minimum_required(VERSION 3.14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /build)
# This is a single line comment
project(CAPTAIN_SONAR VERSION 1.0.0 LANGUAGES C CXX)
add_executable(sonar src/main.cc)
include_directories(
    include
)

add_library(renderer STATIC include/renderer.cc include/texture.cc)

add_subdirectory(lib/SDL STATIC)

#target_link_libraries(sonar PRIVATE ncurses)
target_link_libraries(renderer PRIVATE SDL3::SDL3)
target_link_libraries(sonar PRIVATE renderer)
target_link_libraries(sonar PRIVATE SDL3::SDL3)