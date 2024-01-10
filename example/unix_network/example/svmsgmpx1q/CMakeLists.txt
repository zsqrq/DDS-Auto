cmake_minimum_required(VERSION 3.22)
project(UnixSvmsgmpx)

add_executable(unix_network_svmsgmpx1q_servermain server_main.cpp)
target_link_libraries(unix_network_svmsgmpx1q_servermain
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svmsgmpx1q_servermain
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svmsgmpx1q/${BIN_INSTALL_DIR})

add_executable(unix_network_svmsgmpx1q_clientmain client_main.cpp)
target_link_libraries(unix_network_svmsgmpx1q_clientmain
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svmsgmpx1q_clientmain
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svmsgmpx1q/${BIN_INSTALL_DIR})
