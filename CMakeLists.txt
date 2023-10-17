cmake_minimum_required(VERSION 3.22)
project(Fast-DDS-Example 
    DESCRIPTION "Pure Cmake Project For Fast DDS Example")
set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_FIND_ROOT_PATH ${CMAKE_SOURCE_DIR}/cmake)

if(NOT fastddshelper)
    find_package(fastddshelper REQUIRED)
endif()

if(NOT fastcdr_FOUND)
    find_package(fastcdr 2 REQUIRED)
endif()

if(NOT fastrtps_FOUND)
    find_package(fastrtps 2.12 REQUIRED)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(DEFAULT_COMPILE -std=c++17 -latomic -O0 -g3 -Wall -c -fPIC -fPIE -pie -fstack-protector-all -Wtrampolines)
else()
    set(DEFAULT_COMPILE -std=c++17 -O3 -Wall -c -fmessage-length=0 -fPIC -fPIE -pie -fstack-protector-all -Wtrampolines)
endif()

add_link_options(-Wl,--disable-new-dtags)
set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib;$ORIGIN/../lib/fast-dds;$ORIGIN/../lib/cyclone-dds")

include_directories(
    ${CMAKE_INSTALL_PREFIX}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Fast_DDS_INC_DIR}
    ${Option_Parser_INC_DIR}
)
link_directories(
    ${CMAKE_INSTALL_PREFIX}/lib
    ${CMAKE_INSTALL_PREFIX}/lib/fast-dds
    ${CMAKE_INSTALL_PREFIX}/lib/cyclone-dds
)

message(WARNING "Install path is : ${CMAKE_INSTALL_PREFIX}")

add_subdirectory(thirdparty)
add_subdirectory(example)