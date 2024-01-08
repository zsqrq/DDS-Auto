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

add_executable(unix_network_pxmesg_mqcreate mqcreate.cpp)
target_link_libraries(unix_network_pxmesg_mqcreate
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxmesg_mqcreate
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxmsgque/${BIN_INSTALL_DIR})

add_executable(unix_network_pxmesg_mqsend mqsend.cpp)
target_link_libraries(unix_network_pxmesg_mqsend
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxmesg_mqsend
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxmsgque/${BIN_INSTALL_DIR})

add_executable(unix_network_pxmesg_mqreceive mqreceive.cpp)
target_link_libraries(unix_network_pxmesg_mqreceive
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxmesg_mqreceive
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxmsgque/${BIN_INSTALL_DIR})

add_executable(unix_network_pxmesg_mqsysconf mqsysconf.cpp)
target_link_libraries(unix_network_pxmesg_mqsysconf
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxmesg_mqsysconf
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxmsgque/${BIN_INSTALL_DIR})

add_executable(unix_network_pxmesg_mqnotifysig1 mqnotifysig1.cpp)
target_link_libraries(unix_network_pxmesg_mqnotifysig1
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxmesg_mqnotifysig1
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxmsgque/${BIN_INSTALL_DIR})

add_executable(unix_network_pxmesg_mqnotifysig2 mqnotifysig2.cpp)
target_link_libraries(unix_network_pxmesg_mqnotifysig2
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxmesg_mqnotifysig2
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxmsgque/${BIN_INSTALL_DIR})

add_executable(unix_network_pxmesg_mqnotifysig3 mqnotifysig3.cpp)
target_link_libraries(unix_network_pxmesg_mqnotifysig3
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxmesg_mqnotifysig3
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxmsgque/${BIN_INSTALL_DIR})

add_executable(unix_network_pxmesg_mqnotifysig4 mqnotifysig4.cpp)
target_link_libraries(unix_network_pxmesg_mqnotifysig4
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxmesg_mqnotifysig4
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxmsgque/${BIN_INSTALL_DIR})

add_executable(unix_network_pxmesg_mqnotifysig5 mqnotifysig5.cpp)
target_link_libraries(unix_network_pxmesg_mqnotifysig5
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxmesg_mqnotifysig5
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxmsgque/${BIN_INSTALL_DIR})

add_executable(unix_network_pxmesg_mqnotifythread1 mqnotifythread1.cpp)
target_link_libraries(unix_network_pxmesg_mqnotifythread1
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxmesg_mqnotifythread1
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxmsgque/${BIN_INSTALL_DIR})