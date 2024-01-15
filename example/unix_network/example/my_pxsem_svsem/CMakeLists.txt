cmake_minimum_required(VERSION 3.22)
project(UnixIpcPxsemSvsem)

add_library(unix-network-mysemsvsem-lib SHARED
    sem_open.cpp
)

target_link_libraries(unix-network-mysemsvsem-lib
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
    PUBLIC glog::glog
    PUBLIC unix-network-ipc-lib
)

install(TARGETS unix-network-mysemsvsem-lib
    LIBRARY
    DESTINATION lib)