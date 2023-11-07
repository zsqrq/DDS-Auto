list(APPEND CMAKE_FIND_ROOT_PATH ${CMAKE_SOURCE_DIR}/thirdparty/fast-dds/share/fastrtps/cmake)
list(APPEND CMAKE_FIND_ROOT_PATH ${CMAKE_SOURCE_DIR}/thirdparty/fast-dds/lib/cmake/fastcdr)
list(APPEND CMAKE_FIND_ROOT_PATH ${CMAKE_SOURCE_DIR}/thirdparty/fast-dds/lib/foonathan_memory/cmake)
list(APPEND CMAKE_FIND_ROOT_PATH ${CMAKE_SOURCE_DIR}/thirdparty/Boost/lib/cmake/Boost-1.83.0)
list(APPEND CMAKE_FIND_ROOT_PATH ${CMAKE_SOURCE_DIR}/thirdparty/glog/lib/cmake/glog)

set(fastcdr_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/fast-dds/lib/cmake/fastcdr CACHE INTERNAL "")
set(foonathan_ROOT_DIR  ${CMAKE_SOURCE_DIR}/thirdparty/fast-dds/lib/foonathan_memory/cmake CACHE INTERNAL "")
set(fastrtps_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/fast-dds/share/fastrtps/cmake CACHE INTERNAL "")

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(CheckCXXCompilerFlag)
include(${CMAKE_SOURCE_DIR}/cmake/tros-tool.cmake)

set(Fast_DDS_INC_DIR ${CMAKE_SOURCE_DIR}/thirdparty/fast-dds/include CACHE INTERNAL "")
set(GLOG_INC_DIR ${CMAKE_SOURCE_DIR}/thirdparty/glog/include CACHE INTERNAL "")
set(Option_Parser_INC_DIRS 
${CMAKE_SOURCE_DIR}/thirdparty/fast-dds/include/fastdds/thirdparty/optionparser 
${CMAKE_SOURCE_DIR}/thirdparty/fast-dds/include/fastdds/thirdparty/optionparser/optionparser
CACHE INTERNAL "")
set(BOOST_LIB_DIR ${CMAKE_SOURCE_DIR}/thirdparty/Boost/lib CACHE INTERNAL "")

list(APPEND MY_RPATHS 
    "${CMAKE_INSTALL_PREFIX}/lib" 
    "${CMAKE_INSTALL_PREFIX}/lib/fast-dds"
    "${CMAKE_INSTALL_PREFIX}/lib/cyclone-dds")

set(DDS_RUN_PATHS ${MY_RPATHS} CACHE INTERNAL "")