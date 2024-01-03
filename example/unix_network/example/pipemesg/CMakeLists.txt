cmake_minimum_required(VERSION 3.22)
project(UnixPipeMesg)

add_executable(unix_network_pipemesg_fifo mainfifo.cpp mesg.h)
target_link_libraries(unix_network_pipemesg_fifo
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pipemesg_fifo
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pipemesg/${BIN_INSTALL_DIR})