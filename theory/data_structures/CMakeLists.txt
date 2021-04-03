cmake_minimum_required(VERSION 3.2)

project(test)

add_subdirectory(lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")

add_executable(test main.cpp)

target_include_directories(test
	PUBLIC "${PROJECT_BINARY_DIR}"
	PUBLIC "${PROJECT_SOURCE_DIR}/lib"
	)

target_link_libraries(test
	PUBLIC data_structures)


