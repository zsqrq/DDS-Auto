cmake_minimum_required(VERSION 3.22)
project(UnixPipe)

add_executable(unix_network_mainpipe mainpipe.cpp client.cpp server.cpp)

target_link_libraries(unix_network_mainpipe
    PUBLIC unix-network-ipc-lib
)

install(TARGETS unix_network_mainpipe
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pipe/${BIN_INSTALL_DIR})

add_executable(unix_network_uplex fduplex.cpp)

target_link_libraries(unix_network_uplex
    PUBLIC unix-network-ipc-lib
)

install(TARGETS unix_network_uplex
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pipe/${BIN_INSTALL_DIR})

add_executable(unix_network_mainpopen mainpopen.cpp)

target_link_libraries(unix_network_mainpopen
    PUBLIC unix-network-ipc-lib
)

install(TARGETS unix_network_mainpopen
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pipe/${BIN_INSTALL_DIR})

add_executable(unix_network_mainfifo mainfifo.cpp)

target_link_libraries(unix_network_mainfifo
    PUBLIC unix-network-ipc-lib
)

install(TARGETS unix_network_mainfifo
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pipe/${BIN_INSTALL_DIR})

add_executable(unix_network_servermain server_main.cpp server.cpp)
target_link_libraries(unix_network_servermain
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_servermain
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pipe/${BIN_INSTALL_DIR})

add_executable(unix_network_clientmain client.cpp client_main.cpp)
target_link_libraries(unix_network_clientmain
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_clientmain
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pipe/${BIN_INSTALL_DIR})