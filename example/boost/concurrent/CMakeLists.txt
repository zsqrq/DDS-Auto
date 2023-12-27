cmake_minimum_required(VERSION 3.22)

project(ConcurrentExample VERSION 1 LANGUAGES CXX)

add_executable(example01_thread example01_thread.cpp)
target_link_libraries(example01_thread
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
    PUBLIC glog::glog
)
install(TARGETS example01_thread
    RUNTIME
    DESTINATION examples/cpp/boost/conurrent/${BIN_INSTALL_DIR})

add_executable(example01_mutexlock example02_mutexlock.cpp)
target_link_libraries(example01_mutexlock
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
    PUBLIC glog::glog
)
install(TARGETS example01_mutexlock
    RUNTIME
    DESTINATION examples/cpp/boost/conurrent/${BIN_INSTALL_DIR})

