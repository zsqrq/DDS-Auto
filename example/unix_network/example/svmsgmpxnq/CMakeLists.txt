cmake_minimum_required(VERSION 3.22)
project(UnixSvmsgmpxnq)

add_executable(unix_network_svmsgmpxnq_clientmain client_main.cpp)
target_link_libraries(unix_network_svmsgmpxnq_clientmain
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svmsgmpxnq_clientmain
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svmsgmpxnq/${BIN_INSTALL_DIR})

add_executable(unix_network_svmsgmpxnq_servermain server_main.cpp)
target_link_libraries(unix_network_svmsgmpxnq_servermain
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svmsgmpxnq_servermain
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svmsgmpxnq/${BIN_INSTALL_DIR})