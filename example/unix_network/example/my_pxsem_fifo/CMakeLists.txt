cmake_minimum_required(VERSION 3.22)
project(UnixIpcPxsemFifo)

add_library(unix-network-mysemfifo-lib
    sem_open.cpp
    sem_close.cpp
    sem_post.cpp)

target_link_libraries(unix-network-mysemfifo-lib
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
    PUBLIC glog::glog
    PUBLIC unix-network-ipc-lib
)

install(TARGETS unix-network-mysemfifo-lib
    LIBRARY
    DESTINATION lib)