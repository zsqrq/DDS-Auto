cmake_minimum_required(VERSION 3.22)

project(Json_ID_client VERSION 1 LANGUAGES CXX)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS_)
add_executable(Json_ID_client ${SRCS_})
#add_executable(Asio_AsyncServer02 AsyncServer_Main02.cpp)
target_link_libraries(Json_ID_client
    PUBLIC ${Asio_Socket_LIBS}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC glog::glog
    PRIVATE protobuf-server-msg
    PRIVATE jsoncpp
    )
install(TARGETS Json_ID_client
    RUNTIME
    DESTINATION examples/cpp/boost/asio/socket/MsgID_JsonServer/${BIN_INSTALL_DIR})