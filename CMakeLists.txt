cmake_minimum_required(VERSION 2.8)
project(test)

set(SRC_LIST main.cpp)
add_definitions(--std=c++11)
include_directories(.)
link_directories(.)

add_executable(test ${SRC_LIST})

target_link_libraries(test pthread )



