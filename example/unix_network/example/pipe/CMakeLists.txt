cmake_minimum_required(VERSION 3.22)
project(UnixPipe)

add_executable(unix_network_mainpipe mainpipe.cpp client.cpp server.cpp)

target_link_libraries(unix_network_mainpipe
    PUBLIC unix-network-ipc-lib
)

install(TARGETS unix_network_mainpipe
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pipe/${BIN_INSTALL_DIR})
