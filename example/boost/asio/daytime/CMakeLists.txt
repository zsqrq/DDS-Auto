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

add_executable(Sync_udp_daytime_client Sync_udp_daytime_client.cpp)
target_link_libraries(Sync_udp_daytime_client
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
)
install(TARGETS Sync_udp_daytime_client
RUNTIME 
DESTINATION examples/cpp/boost/asio/daytime/${BIN_INSTALL_DIR})

add_executable(Sync_udp_daytime_server Sync_udp_daytime_server.cpp)
target_link_libraries(Sync_udp_daytime_server
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
)
install(TARGETS Sync_udp_daytime_server
RUNTIME 
DESTINATION examples/cpp/boost/asio/daytime/${BIN_INSTALL_DIR})

add_executable(Async_udp_daytime_server Async_udp_daytime_server.cpp)
target_link_libraries(Async_udp_daytime_server
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
)
install(TARGETS Async_udp_daytime_server
RUNTIME 
DESTINATION examples/cpp/boost/asio/daytime/${BIN_INSTALL_DIR})

add_executable(Combined_tcp_udp_async_server Combined_tcp_udp_async_server.cpp)
target_link_libraries(Combined_tcp_udp_async_server
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
)
install(TARGETS Combined_tcp_udp_async_server
RUNTIME 
DESTINATION examples/cpp/boost/asio/daytime/${BIN_INSTALL_DIR})

add_executable(Async_udp_daytime_client Async_udp_daytime_client.cpp)
target_link_libraries(Async_udp_daytime_client
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
)
install(TARGETS Async_udp_daytime_client
RUNTIME 
DESTINATION examples/cpp/boost/asio/daytime/${BIN_INSTALL_DIR})

add_executable(async_server_test async_server_test.cpp)
target_link_libraries(async_server_test
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
)
install(TARGETS async_server_test
RUNTIME 
DESTINATION examples/cpp/boost/asio/daytime/${BIN_INSTALL_DIR})

add_executable(async_client_test async_client_test.cpp)
target_link_libraries(async_client_test
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
)
install(TARGETS async_client_test
RUNTIME 
DESTINATION examples/cpp/boost/asio/daytime/${BIN_INSTALL_DIR})