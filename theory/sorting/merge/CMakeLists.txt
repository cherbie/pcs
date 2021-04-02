cmake_minimum_required(VERSION 3.2)
project(merge)

set(SOURCE_FILES "merge_sort.cpp")

add_executable(merge ${SOURCE_FILES})

target_include_directories(merge
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# actually places in global '/usr/bin' directory
# install(TARGETS merge DESTINATION bin)

