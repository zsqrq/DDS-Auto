cmake_minimum_required(VERSION 3.22)
project(UnixRtSignals)

add_executable(unix_network_rtsignals_test1 test1.cpp)
target_link_libraries(unix_network_rtsignals_test1
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_rtsignals_test1
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/rtsignals/${BIN_INSTALL_DIR})
