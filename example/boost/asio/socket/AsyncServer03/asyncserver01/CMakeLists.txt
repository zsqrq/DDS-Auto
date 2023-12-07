cmake_minimum_required(VERSION 3.22)

project(Asio_asyncserver01 VERSION 1 LANGUAGES CXX)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS_)
add_executable(Asio_asyncserver01 ${SRCS_})
#add_executable(Asio_AsyncServer02 AsyncServer_Main02.cpp)
target_link_libraries(Asio_asyncserver01
    PUBLIC ${Asio_Socket_LIBS}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC glog::glog
    )
install(TARGETS Asio_asyncserver01
    RUNTIME
    DESTINATION examples/cpp/boost/asio/socket/AsyncServer03/${BIN_INSTALL_DIR})