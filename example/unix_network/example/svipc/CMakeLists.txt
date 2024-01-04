cmake_minimum_required(VERSION 3.22)
project(UnixSvipc)

add_executable(unix_network_ftok ftok.cpp)

target_link_libraries(unix_network_ftok
    PUBLIC unix-network-ipc-lib
)

install(TARGETS unix_network_ftok
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svipc/${BIN_INSTALL_DIR})
