cmake_minimum_required(VERSION 3.22)
project(UnixIpcShm)

add_executable(unix_network_shm_incrl incrl.cpp)
target_link_libraries(unix_network_shm_incrl
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_shm_incrl
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/shm/${BIN_INSTALL_DIR})