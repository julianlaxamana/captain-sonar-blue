cmake_minimum_required(VERSION 3.14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./out)
# This is a single line comment
project(CAPTAIN_SONAR VERSION 1.0.0 LANGUAGES C CXX)
add_executable(sonar src/main.cc)
include_directories(
    include
)

add_library(renderer STATIC include/renderer.cc include/texture.cc include/button.cc include/font.cc)

add_subdirectory(lib/SDL)
add_subdirectory(lib/SDL_ttf )

#target_link_libraries(sonar PRIVATE ncurses)
target_link_libraries(renderer PRIVATE SDL3::SDL3)
target_link_libraries(renderer PRIVATE SDL3_ttf::SDL3_ttf)

target_link_libraries(sonar PRIVATE renderer)
target_link_libraries(sonar PRIVATE harfbuzz)
target_link_libraries(sonar PRIVATE SDL3::SDL3)
target_link_libraries(sonar PRIVATE SDL3_ttf::SDL3_ttf)

SET(GCC_COVERAGE_LINK_FLAGS "-DSDLTTF_VENDORED=OFF")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

