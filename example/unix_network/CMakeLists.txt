cmake_minimum_required(VERSION 3.22)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
    /usr/include/tirpc)

add_subdirectory(lib)
add_subdirectory(example)