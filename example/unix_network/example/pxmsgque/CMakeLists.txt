cmake_minimum_required(VERSION 3.22)
project(UnixPxmsgQue)

add_executable(unix_network_pxmesg_que mqcreat1.cpp)
target_link_libraries(unix_network_pxmesg_que
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxmesg_que
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxmsgque/${BIN_INSTALL_DIR})

add_executable(unix_network_pxmesg_unlink mqunlink.cpp)
target_link_libraries(unix_network_pxmesg_unlink
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxmesg_unlink
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxmsgque/${BIN_INSTALL_DIR})

add_executable(unix_network_pxmesg_mqgetattr mqgetattr.cpp)
target_link_libraries(unix_network_pxmesg_mqgetattr
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxmesg_mqgetattr
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxmsgque/${BIN_INSTALL_DIR})