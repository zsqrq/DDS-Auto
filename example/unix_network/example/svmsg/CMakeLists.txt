cmake_minimum_required(VERSION 3.22)
project(UnixSvmsg)

add_executable(unix_network_slot slot.cpp)
target_link_libraries(unix_network_slot
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_slot
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svmsg/${BIN_INSTALL_DIR})

add_executable(unix_network_ctl ctl.cpp)
target_link_libraries(unix_network_ctl
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_ctl
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svmsg/${BIN_INSTALL_DIR})

add_executable(unix_network_msgcreate msgcreate.cpp)
target_link_libraries(unix_network_msgcreate
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_msgcreate
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svmsg/${BIN_INSTALL_DIR})

add_executable(unix_network_msgsend msgsend.cpp)
target_link_libraries(unix_network_msgsend
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_msgsend
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svmsg/${BIN_INSTALL_DIR})

add_executable(unix_network_msgrcv msgrcv.cpp)
target_link_libraries(unix_network_msgrcv
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_msgrcv
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svmsg/${BIN_INSTALL_DIR})

add_executable(unix_network_msgrmid msgrmid.cpp)
target_link_libraries(unix_network_msgrmid
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_msgrmid
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svmsg/${BIN_INSTALL_DIR})
