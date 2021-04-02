cmake_minimum_required(VERSION 3.2)
project(bubble)

set(SOURCE_FILES "bubble_sort.cpp")

add_executable(bubble ${SOURCE_FILES})

target_include_directories(bubble
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# actually places in global '/usr/bin' directory
# install(TARGETS bubble DESTINATION bin)

