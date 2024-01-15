cmake_minimum_required(VERSION 3.22)
project(UnixIpcPxsemMmap)

add_library(unix-network-mysemmmap-lib SHARED
    sem_open.cpp
    sem_close.cpp
    sem_unlink.cpp
    sem_post.cpp
    sem_wait.cpp
    sem_trywait.cpp
    sem_getvalue.cpp
)

target_link_libraries(unix-network-mysemmmap-lib
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
    PUBLIC glog::glog
    PUBLIC unix-network-ipc-lib
)

install(TARGETS unix-network-mysemmmap-lib
    LIBRARY
    DESTINATION lib)