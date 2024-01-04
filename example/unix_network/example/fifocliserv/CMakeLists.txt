cmake_minimum_required(VERSION 3.22)
project(UnixFIFOcliserv)

add_executable(unix_network_fifocli mainclient.cpp)
target_link_libraries(unix_network_fifocli
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_fifocli
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/fifocliserv/${BIN_INSTALL_DIR})

add_executable(unix_network_fifoserver mainserver.cpp)
target_link_libraries(unix_network_fifoserver
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_fifoserver
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/fifocliserv/${BIN_INSTALL_DIR})