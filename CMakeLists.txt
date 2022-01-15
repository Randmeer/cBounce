cmake_minimum_required(VERSION 3.21)
project(cbounce)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(cbounce main.cpp)

target_link_libraries(cbounce ${CURSES_LIBRARIES})
