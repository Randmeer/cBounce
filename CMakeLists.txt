cmake_minimum_required(VERSION 3.21)
project(bouncing_logo)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(bouncing_logo main.cpp)

target_link_libraries(bouncing_logo ${CURSES_LIBRARIES})
