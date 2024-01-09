cmake_minimum_required(VERSION 3.22)
project(UnixSvmsgCliserv)

add_executable(unix_network_svmsg_cliservmain server_main.cpp)
target_link_libraries(unix_network_svmsg_cliservmain
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svmsg_cliservmain
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svmsgcliserv/${BIN_INSTALL_DIR})

add_executable(unix_network_svmsg_cliclientmain client_main.cpp)
target_link_libraries(unix_network_svmsg_cliclientmain
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svmsg_cliclientmain
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svmsgcliserv/${BIN_INSTALL_DIR})