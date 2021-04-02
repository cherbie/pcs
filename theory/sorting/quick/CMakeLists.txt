cmake_minimum_required(VERSION 3.2)
project(quick)

set(SOURCE_FILES "quick_sort.cpp")

add_executable(quick ${SOURCE_FILES})

target_include_directories(quick
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# actually places in global '/usr/bin' directory
# install(TARGETS quick DESTINATION bin)

