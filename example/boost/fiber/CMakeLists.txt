cmake_minimum_required(VERSION 3.22)

project(Fiber VERSION 1 LANGUAGES CXX)



add_executable(fiber_async_callback fiber_test_main.cpp)
target_link_libraries(fiber_async_callback
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
    PUBLIC boost_fiber
    PUBLIC boost_unit_test_framework
    PUBLIC glog::glog
    )
install(TARGETS fiber_async_callback
    RUNTIME
    DESTINATION examples/cpp/boost/fiber/${BIN_INSTALL_DIR})

add_executable(fiber_test_01 fiber_test_01.cpp)
target_link_libraries(fiber_test_01
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
    PUBLIC boost_fiber
    PUBLIC boost_unit_test_framework
    PUBLIC glog::glog
    )
install(TARGETS fiber_test_01
    RUNTIME
    DESTINATION examples/cpp/boost/fiber/${BIN_INSTALL_DIR})