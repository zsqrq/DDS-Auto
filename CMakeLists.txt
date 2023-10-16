cmake_minimum_required(VERSION 3.22)
project(Fast-DDS-Example 
    DESCRIPTION "Pure Cmake Project For Fast DDS Example")
set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_FIND_ROOT_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

if(NOT fastddshelper)
    find_package(fastddshelper REQUIRED)
endif()

if(NOT fastcdr_FOUND)
    find_package(fastcdr 2 REQUIRED)
endif()

if(NOT fastrtps_FOUND)
    find_package(fastrtps 2.12 REQUIRED)
endif()

include(CheckCXXCompilerFlag)