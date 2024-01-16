cmake_minimum_required(VERSION 3.22)
project(UnixIpcShm)

add_executable(unix_network_shm_incrl incrl.cpp)
target_link_libraries(unix_network_shm_incrl
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_shm_incrl
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/shm/${BIN_INSTALL_DIR})

add_executable(unix_network_shm_incr2 incr2.cpp)
target_link_libraries(unix_network_shm_incr2
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_shm_incr2
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/shm/${BIN_INSTALL_DIR})

add_executable(unix_network_shm_incr3 incr3.cpp)
target_link_libraries(unix_network_shm_incr3
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_shm_incr3
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/shm/${BIN_INSTALL_DIR})

add_executable(unix_network_shm_incr_map_anon incr_map_anon.cpp)
target_link_libraries(unix_network_shm_incr_map_anon
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_shm_incr_map_anon
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/shm/${BIN_INSTALL_DIR})

add_executable(unix_network_shm_incr_dev_zero incr_dev_zero.cpp)
target_link_libraries(unix_network_shm_incr_dev_zero
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_shm_incr_dev_zero
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/shm/${BIN_INSTALL_DIR})

add_executable(unix_network_shm_tets1 test1.cpp)
target_link_libraries(unix_network_shm_tets1
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_shm_tets1
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/shm/${BIN_INSTALL_DIR})