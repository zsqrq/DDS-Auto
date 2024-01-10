cmake_minimum_required(VERSION 3.22)
project(UnixIpcMutex)

add_executable(unix_network_mutex_prodcons2 prodcons2.cpp)
target_link_libraries(unix_network_mutex_prodcons2
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_mutex_prodcons2
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/mutex/${BIN_INSTALL_DIR})

add_executable(unix_network_mutex_prodcons3 prodcons3.cpp)
target_link_libraries(unix_network_mutex_prodcons3
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_mutex_prodcons3
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/mutex/${BIN_INSTALL_DIR})

add_executable(unix_network_mutex_prodcons6 prodcons6.cpp)
target_link_libraries(unix_network_mutex_prodcons6
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_mutex_prodcons6
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/mutex/${BIN_INSTALL_DIR})