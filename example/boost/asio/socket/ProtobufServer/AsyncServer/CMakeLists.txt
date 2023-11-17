cmake_minimum_required(VERSION 3.22)

project(Proto_async_server VERSION 1 LANGUAGES CXX)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS_)
add_executable(Proto_async_server ${SRCS_})
#add_executable(Asio_AsyncServer02 AsyncServer_Main02.cpp)
target_link_libraries(Proto_async_server
    PUBLIC ${Asio_Socket_LIBS}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC glog::glog
    PRIVATE protobuf-server-msg
    )
install(TARGETS Proto_async_server
    RUNTIME
    DESTINATION examples/cpp/boost/asio/socket/ProtobufServer/${BIN_INSTALL_DIR})