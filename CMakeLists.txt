cmake_minimum_required(VERSION 3.21)
project(cBounce)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(cBounce main.cpp)

target_link_libraries(cBounce ${CURSES_LIBRARIES})
