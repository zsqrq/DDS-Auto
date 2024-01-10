cmake_minimum_required(VERSION 3.22)
project(UnixIpcLock)

add_executable(unix_network_lock_main lockmain.cpp)
target_link_libraries(unix_network_lock_main
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_lock_main
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/lock/${BIN_INSTALL_DIR})
