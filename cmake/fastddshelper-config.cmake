list(APPEND CMAKE_FIND_ROOT_PATH ${CMAKE_SOURCE_DIR}/thirdparty/fast-dds/share/fastrtps/cmake)
list(APPEND CMAKE_FIND_ROOT_PATH ${CMAKE_SOURCE_DIR}/thirdparty/fast-dds/lib/cmake/fastcdr)
list(APPEND CMAKE_FIND_ROOT_PATH ${CMAKE_SOURCE_DIR}/thirdparty/fast-dds/lib/foonathan_memory/cmake)

set(fastcdr_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/fast-dds/lib/cmake/fastcdr CACHE INTERNAL "")
set(foonathan_ROOT_DIR  ${CMAKE_SOURCE_DIR}/thirdparty/fast-dds/lib/foonathan_memory/cmake CACHE INTERNAL "")
set(fastrtps_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/fast-dds/share/fastrtps/cmake CACHE INTERNAL "")

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(CheckCXXCompilerFlag)
include(${CMAKE_SOURCE_DIR}/cmake/tros-tool.cmake)
