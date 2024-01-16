cmake_minimum_required(VERSION 3.22)
project(UnixIpcPxsemsvsem)

add_executable(unix_network_svsem_semcreate semcreate.cpp)
target_link_libraries(unix_network_svsem_semcreate
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svsem_semcreate
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svsem/${BIN_INSTALL_DIR})

add_executable(unix_network_svsem_semrmid semrmid.cpp)
target_link_libraries(unix_network_svsem_semrmid
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svsem_semrmid
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svsem/${BIN_INSTALL_DIR})

add_executable(unix_network_svsem_semsetvalues semsetvalues.cpp)
target_link_libraries(unix_network_svsem_semsetvalues
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svsem_semsetvalues
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svsem/${BIN_INSTALL_DIR})

add_executable(unix_network_svsem_semgetvalues semgetvalues.cpp)
target_link_libraries(unix_network_svsem_semgetvalues
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svsem_semgetvalues
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svsem/${BIN_INSTALL_DIR})

add_executable(unix_network_svsem_semops semops.cpp)
target_link_libraries(unix_network_svsem_semops
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svsem_semops
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svsem/${BIN_INSTALL_DIR})

add_executable(unix_network_svsem_limits limits.cpp)
target_link_libraries(unix_network_svsem_limits
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_svsem_limits
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/svsem/${BIN_INSTALL_DIR})