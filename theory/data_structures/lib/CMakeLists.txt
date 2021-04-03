cmake_minimum_required(VERSION 3.2)

project(data_structures)

set(SOURCE_FILES linked_list.cpp linked_list.hpp)

add_library(data_structures SHARED ${SOURCE_FILES})

target_include_directories(data_structures PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")


