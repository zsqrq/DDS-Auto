cmake_minimum_required(VERSION 3.22)
project(UnixSvmsg)

add_executable(unix_network_slot slot.cpp)

target_link_libraries(unix_network_slot
    PUBLIC unix-network-ipc-lib
)

install(TARGETS unix_network_slot
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svmsg/${BIN_INSTALL_DIR})
