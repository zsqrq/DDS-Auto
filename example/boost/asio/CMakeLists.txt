cmake_minimum_required(VERSION 3.22)

project(BoostAsio VERSION 1 LANGUAGES CXX)

add_executable(Asio_timer_sync_test timer_synchronoous.cpp)

target_link_libraries(Asio_timer_sync_test
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
)

install(TARGETS Asio_timer_sync_test
RUNTIME 
DESTINATION examples/cpp/boost/asio/${BIN_INSTALL_DIR})

add_executable(Asio_timer_async_test timer_asynchronous.cpp)
target_link_libraries(Asio_timer_async_test
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
)
install(TARGETS Asio_timer_async_test
RUNTIME 
DESTINATION examples/cpp/boost/asio/${BIN_INSTALL_DIR})

add_executable(Asio_timer_bind_args timer_binding_args.cpp)
target_link_libraries(Asio_timer_bind_args
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
)
install(TARGETS Asio_timer_bind_args
RUNTIME 
DESTINATION examples/cpp/boost/asio/${BIN_INSTALL_DIR})

add_executable(Asio_mem_func_handle mem_func_as_handle.cpp)
target_link_libraries(Asio_mem_func_handle
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
)
install(TARGETS Asio_mem_func_handle
RUNTIME 
DESTINATION examples/cpp/boost/asio/${BIN_INSTALL_DIR})

add_executable(Asio_sync_handle_multithreads sync_handles_multithreading.cpp)
target_link_libraries(Asio_sync_handle_multithreads
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
)
install(TARGETS Asio_sync_handle_multithreads
RUNTIME 
DESTINATION examples/cpp/boost/asio/${BIN_INSTALL_DIR})