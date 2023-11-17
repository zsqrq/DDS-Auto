cmake_minimum_required(VERSION 3.22)

project(Proto_sync_client VERSION 1 LANGUAGES CXX)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS_)
add_executable(Proto_sync_client ${SRCS_})
#add_executable(Asio_AsyncServer02 AsyncServer_Main02.cpp)
target_link_libraries(Proto_sync_client
    PUBLIC ${Asio_Socket_LIBS}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC glog::glog
    PRIVATE protobuf-server-msg
    )
install(TARGETS Proto_sync_client
    RUNTIME
    DESTINATION examples/cpp/boost/asio/socket/ProtobufServer/${BIN_INSTALL_DIR})