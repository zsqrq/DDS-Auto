cmake_minimum_required(VERSION 3.22)

project(IoContextPoolClient VERSION 1 LANGUAGES CXX)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS_)
add_executable(IoContextPoolClient ${SRCS_})
#add_executable(Asio_AsyncServer02 AsyncServer_Main02.cpp)
target_link_libraries(IoContextPoolClient
    PUBLIC ${Asio_Socket_LIBS}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC glog::glog
    PRIVATE protobuf-server-msg
    PRIVATE jsoncpp
    )
install(TARGETS IoContextPoolClient
    RUNTIME
    DESTINATION examples/cpp/boost/asio/socket/IoContextPoolServer/${BIN_INSTALL_DIR})