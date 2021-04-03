cmake_minimum_required(VERSION 3.2)

project(sorting)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")

add_subdirectory(bubble)
add_subdirectory(merge)
add_subdirectory(quick)
add_subdirectory(binary)
