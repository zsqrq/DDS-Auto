cmake_minimum_required(VERSION 3.22)

project(ThreadPoolClient VERSION 1 LANGUAGES CXX)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS_)
add_executable(ThreadPoolClient ${SRCS_})
#add_executable(Asio_AsyncServer02 AsyncServer_Main02.cpp)
target_link_libraries(ThreadPoolClient
    PUBLIC ${Asio_Socket_LIBS}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC glog::glog
    PRIVATE protobuf-server-msg
    PRIVATE jsoncpp
    )
install(TARGETS ThreadPoolClient
    RUNTIME
    DESTINATION examples/cpp/boost/asio/socket/ThreadPoolServer/${BIN_INSTALL_DIR})