cmake_minimum_required(VERSION 3.22)

project(Daytime VERSION 1 LANGUAGES CXX)

add_executable(Sync_tcp_client_daytime Sync_tcp_client_daytime.cpp)
target_link_libraries(Sync_tcp_client_daytime
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
)
install(TARGETS Sync_tcp_client_daytime
RUNTIME 
DESTINATION examples/cpp/boost/asio/daytime/${BIN_INSTALL_DIR})

add_executable(Sync_tcp_server_daytime Sync_tcp_server_daytime.cpp)
target_link_libraries(Sync_tcp_server_daytime
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
)
install(TARGETS Sync_tcp_server_daytime
RUNTIME 
DESTINATION examples/cpp/boost/asio/daytime/${BIN_INSTALL_DIR})

add_executable(Async_tcp_daytime_server Async_tcp_daytime_server.cpp)
target_link_libraries(Async_tcp_daytime_server
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
)
install(TARGETS Async_tcp_daytime_server
RUNTIME 
DESTINATION examples/cpp/boost/asio/daytime/${BIN_INSTALL_DIR})
