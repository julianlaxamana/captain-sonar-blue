cmake_minimum_required(VERSION 3.14)

project(CAPTAIN_SONAR VERSION 1.0.0 LANGUAGES C CXX)

find_package(Boost REQUIRED COMPONENTS system)

# Common dependencies
add_library(common_lib INTERFACE)

target_link_libraries(common_lib INTERFACE
	ncurses
    Boost::system
)

# Global properties
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Server
add_executable(server src/server.cc)
target_link_libraries(server PRIVATE common_lib)

# Client
add_executable(server src/server.cc)
target_link_libraries(server PRIVATE common_lib)
