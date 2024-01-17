cmake_minimum_required(VERSION 3.22)
project(UnixIpcSystemVShm)

add_executable(unix_network_svshm_shmget shmget.cpp)
target_link_libraries(unix_network_svshm_shmget
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svshm_shmget
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svshm/${BIN_INSTALL_DIR})

add_executable(unix_network_svshm_shmrmid shmrmid.cpp)
target_link_libraries(unix_network_svshm_shmrmid
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svshm_shmrmid
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svshm/${BIN_INSTALL_DIR})

add_executable(unix_network_svshm_shmwrite shmwrite.cpp)
target_link_libraries(unix_network_svshm_shmwrite
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svshm_shmwrite
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svshm/${BIN_INSTALL_DIR})

add_executable(unix_network_svshm_shmread shmread.cpp)
target_link_libraries(unix_network_svshm_shmread
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svshm_shmread
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svshm/${BIN_INSTALL_DIR})

add_executable(unix_network_svshm_shmlimits limits.cpp)
target_link_libraries(unix_network_svshm_shmlimits
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svshm_shmlimits
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svshm/${BIN_INSTALL_DIR})