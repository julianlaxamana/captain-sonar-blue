cmake_minimum_required(VERSION 3.14)
# This is a single line comment
project(CAPTAIN_SONAR VERSION 1.0.0 LANGUAGES C CXX)
add_executable(sonar src/main.cc)
target_link_libraries(sonar PRIVATE ncurses)
