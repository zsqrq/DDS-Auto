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

add_executable(example02_mutexlock example02_mutexlock.cpp)
target_link_libraries(example02_mutexlock
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
    PUBLIC glog::glog
)
install(TARGETS example02_mutexlock
    RUNTIME
    DESTINATION examples/cpp/boost/conurrent/${BIN_INSTALL_DIR})

add_executable(example03_uniquelock example03_uniquelock.cpp)
target_link_libraries(example03_uniquelock
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
    PUBLIC glog::glog
)
install(TARGETS example03_uniquelock
    RUNTIME
    DESTINATION examples/cpp/boost/conurrent/${BIN_INSTALL_DIR})

