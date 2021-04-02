cmake_minimum_required(VERSION 3.2)
project(binary)

set(SOURCE_FILES "binary_search.cpp")

add_executable(binary ${SOURCE_FILES})

target_include_directories(binary
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# actually places in global '/usr/bin' directory
# install(TARGETS bubble DESTINATION bin)

