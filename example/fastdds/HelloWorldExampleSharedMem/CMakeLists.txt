cmake_minimum_required(VERSION 3.22)

project(DDSHelloWorldExampleSharedMem VERSION 1 LANGUAGES CXX)

if(NOT fastcdr_FOUND)
    find_package(fastcdr 2 REQUIRED)
endif()

if(NOT fastrtps_FOUND)
    find_package(fastrtps 2.12 REQUIRED)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    check_cxx_compiler_flag(-std=c++11 SUPPORTS_CXX11)
    if(NOT SUPPORTS_CXX11)
        message(FATAL_ERROR "Compiler doesn't support C++11")
    endif()
endif()

message(STATUS "Configuring HelloWorld example...")
file(GLOB DDS_HELLOWORLD_EXAMPLE_SOURCES_CXX "*.cxx")
file(GLOB DDS_HELLOWORLD_EXAMPLE_SOURCES_CPP "*.cpp")

add_executable(DDSHelloWorldExampleSharedMem 
 ${DDS_HELLOWORLD_EXAMPLE_SOURCES_CXX} 
 ${DDS_HELLOWORLD_EXAMPLE_SOURCES_CPP})

set_target_properties(DDSHelloWorldExampleSharedMem PROPERTIES BUILD_RPATH "${DDS_RUN_PATHS}")

link_directories(
    ${CMAKE_INSTALL_PREFIX}/lib
    ${CMAKE_INSTALL_PREFIX}/lib/fast-dds
    ${CMAKE_INSTALL_PREFIX}/lib/cyclone-dds
    ${CMAKE_SOURCE_DIR}/third_party/lib
)

target_link_libraries(DDSHelloWorldExampleSharedMem
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC glog::glog
    PUBLIC foonathan_memory-0.7.3
)

install(TARGETS DDSHelloWorldExampleSharedMem
    RUNTIME DESTINATION examples/cpp/fastdds/${BIN_INSTALL_DIR})