cmake_minimum_required(VERSION 3.22)
project(UnixIpcPxsem)

add_executable(unix_network_pxsem_semcreate semcreate.cpp)
target_link_libraries(unix_network_pxsem_semcreate
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxsem_semcreate
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxsem/${BIN_INSTALL_DIR})

add_executable(unix_network_pxsem_semunlink semunlink.cpp)
target_link_libraries(unix_network_pxsem_semunlink
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxsem_semunlink
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxsem/${BIN_INSTALL_DIR})

add_executable(unix_network_pxsem_semgetvalue semgetvalue.cpp)
target_link_libraries(unix_network_pxsem_semgetvalue
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxsem_semgetvalue
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxsem/${BIN_INSTALL_DIR})

add_executable(unix_network_pxsem_semwait semwait.cpp)
target_link_libraries(unix_network_pxsem_semwait
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxsem_semwait
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxsem/${BIN_INSTALL_DIR})

add_executable(unix_network_pxsem_sempost sempost.cpp)
target_link_libraries(unix_network_pxsem_sempost
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxsem_sempost
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxsem/${BIN_INSTALL_DIR})

add_executable(unix_network_pxsem_prodcons1 prodcons1.cpp)
target_link_libraries(unix_network_pxsem_prodcons1
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxsem_prodcons1
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxsem/${BIN_INSTALL_DIR})

add_executable(unix_network_pxsem_prodcons2 prodcons2.cpp)
target_link_libraries(unix_network_pxsem_prodcons2
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxsem_prodcons2
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxsem/${BIN_INSTALL_DIR})

add_executable(unix_network_pxsem_prodcons3 prodcons3.cpp)
target_link_libraries(unix_network_pxsem_prodcons3
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxsem_prodcons3
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxsem/${BIN_INSTALL_DIR})

add_executable(unix_network_pxsem_prodcons4 prodcons4.cpp)
target_link_libraries(unix_network_pxsem_prodcons4
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxsem_prodcons4
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxsem/${BIN_INSTALL_DIR})

add_executable(unix_network_pxsem_mycat2 mycat2.cpp)
target_link_libraries(unix_network_pxsem_mycat2
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxsem_mycat2
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxsem/${BIN_INSTALL_DIR})

add_executable(unix_network_pxsem_sysconf semsysconf.cpp)
target_link_libraries(unix_network_pxsem_sysconf
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxsem_sysconf
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxsem/${BIN_INSTALL_DIR})

