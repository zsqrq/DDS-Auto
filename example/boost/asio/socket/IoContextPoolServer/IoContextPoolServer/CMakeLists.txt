cmake_minimum_required(VERSION 3.22)

project(IoContextPoolServer VERSION 1 LANGUAGES CXX)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS_)
add_executable(IoContextPoolServer ${SRCS_})
#add_executable(Asio_AsyncServer02 AsyncServer_Main02.cpp)
target_link_libraries(IoContextPoolServer
    PUBLIC ${Asio_Socket_LIBS}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC glog::glog
    PRIVATE protobuf-server-msg
    PRIVATE jsoncpp
    )
install(TARGETS IoContextPoolServer
    RUNTIME
    DESTINATION examples/cpp/boost/asio/socket/IoContextPoolServer/${BIN_INSTALL_DIR})