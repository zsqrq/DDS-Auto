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