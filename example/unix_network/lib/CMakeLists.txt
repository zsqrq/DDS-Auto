cmake_minimum_required(VERSION 3.22)

project(UnixIpc)

add_library(unix-network-ipc-lib  px_ipc_name.cpp
wrapunix.cpp error.cpp)

target_link_libraries(unix-network-ipc-lib
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
    PUBLIC glog::glog
)

install(TARGETS unix-network-ipc-lib
LIBRARY
DESTINATION lib)