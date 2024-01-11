cmake_minimum_required(VERSION 3.22)
project(UnixIpcLock)

add_executable(unix_network_lock_main lockmain.cpp)
target_link_libraries(unix_network_lock_main
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_lock_main
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/lock/${BIN_INSTALL_DIR})

add_executable(unix_network_lock_test2 test2.cpp)
target_link_libraries(unix_network_lock_test2
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_lock_test2
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/lock/${BIN_INSTALL_DIR})

add_executable(unix_network_lock_test3 test3.cpp)
target_link_libraries(unix_network_lock_test3
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_lock_test3
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/lock/${BIN_INSTALL_DIR})

add_executable(unix_network_lock_onedameon onedameon.cpp)
target_link_libraries(unix_network_lock_onedameon
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_lock_onedameon
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/lock/${BIN_INSTALL_DIR})
