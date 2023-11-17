cmake_minimum_required(VERSION 3.22)

project(ProtobufServer VERSION 1 LANGUAGES CXX)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS_)

generate_protos(${CMAKE_CURRENT_SOURCE_DIR})
add_library(protobuf-server-msg ${SRCS_})
#add_executable(Asio_AsyncServer02 AsyncServer_Main02.cpp)
target_link_libraries(protobuf-server-msg
    PUBLIC ${Asio_Socket_LIBS}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC glog::glog
    PUBLIC protobuf
    )
install(TARGETS protobuf-server-msg
    LIBRARY
    DESTINATION lib)